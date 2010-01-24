[indent=4]


const TITLE: string = "Omap4 Player"


class Omap.PlayerWindow: Omap.MediaWindow
    playlist_view: Gtk.TreeView
    playlist_store: Gtk.ListStore
    playlist_selection: Gtk.TreeSelection
    playlist_control: Omap.PlayListControl

    play_pause_button: Gtk.ToolButton
    add_button: Gtk.ToolButton
    next_button: Gtk.ToolButton
    fullscreen_button: Gtk.ToolButton
    remove_image: Gtk.Image
    video_area: Omap.VideoArea
    seeking_scale: Gtk.Scale
    seeking_adjustment: Gtk.Adjustment
    volume_button: Gtk.VolumeButton
    volume_adjustment: Gtk.Adjustment
    mute_image: Gtk.Image
    previous_volume: double
    muted_icon_name: string
    is_muted: bool
    chooser: Gtk.FileChooserDialog

    update_seeking_scale_id: uint
    stream_position: int64
    stream_duration: int64
    should_resume_playback: bool

    debug_dialog: Omap.DebugDialog

    prop playing: bool
        get
            return playlist_control.state == Gst.State.PLAYING

    init
        setup_model()
        setup_controls()
        setup_widgets()

    def setup_model()
        playlist_store = Omap.PlayListControl.model_new()

    def setup_controls()
        playlist_control = new Omap.PlayListControl(playlist_store)
        playlist_control.eos_message += playlist_control_eos
        playlist_control.error_message += playlist_control_error
        playlist_control.playing += playlist_control_playing
        playlist_control.paused += playlist_control_paused
        playlist_control.stopped += playlist_control_stopped
        playlist_control.moved += playlist_control_moved
        playlist_control.prepare_xwindow_id += playlist_control_xid_prepared

    def setup_widgets()
        title = TITLE
        setup_toolbar()
        setup_notebook()
        setup_seeking()
        video_area.realize()
        main_box.show_all()

    def setup_notebook()
        notebook.append_page(new_playlist_box(), new Gtk.Label("List"))
        notebook.append_page(new_video_box(), new Gtk.Label("Video"))
        notebook.switch_page += def (page, num_page)
            on_notebook_switch_page(num_page)

    def setup_toolbar()
        var prev_button = new Gtk.ToolButton.from_stock(Gtk.STOCK_MEDIA_PREVIOUS)
        prev_button.clicked += on_prev
        toolbar.add(prev_button)

        play_pause_button = new Gtk.ToolButton.from_stock(Gtk.STOCK_MEDIA_PLAY)
        toolbar.add(play_pause_button)
        play_pause_button.clicked += play_pause

        next_button = new Gtk.ToolButton.from_stock(Gtk.STOCK_MEDIA_NEXT)
        toolbar.add(next_button)
        next_button.clicked += next

        var stop_button = new Gtk.ToolButton.from_stock(Gtk.STOCK_MEDIA_STOP)
        toolbar.add(stop_button)
        stop_button.clicked += stop

        toolbar_add_expander()

        var volume_button_item = new Gtk.ToolItem()
        toolbar.add(volume_button_item)
        volume_button = new_volume_button_with_mute()
        volume_button_item.add(volume_button)

        fullscreen_button = new Gtk.ToolButton.from_stock(Gtk.STOCK_FULLSCREEN)
        fullscreen_button.no_show_all = true
        fullscreen_button.clicked += toggle_fullscreen
        toolbar.add(fullscreen_button)

        toolbar_add_expander()

        add_button = new Gtk.ToolButton.from_stock(Gtk.STOCK_ADD)
        toolbar.add(add_button)
        add_button.clicked += on_add

        var remove_button = new Gtk.ToolButton.from_stock(Gtk.STOCK_REMOVE)
        toolbar.add(remove_button)
        remove_button.clicked += on_remove

        toolbar_add_quit_button()

    def setup_seeking()
        seeking_adjustment = new Gtk.Adjustment(0, 0, 100, 0.1, 1, 1)
        seeking_scale = new Gtk.HScale(seeking_adjustment)
        main_box.pack_start(seeking_scale, false, false, 0)

        seeking_scale.no_show_all = true
        seeking_scale.update_policy = Gtk.UpdateType.DISCONTINUOUS
        seeking_scale.button_press_event += on_seeking_scale_pressed
        seeking_scale.button_release_event += on_seeking_scale_released
        seeking_scale.format_value += on_scale_format_value

    def play()
        playlist_control.play()

    def pause()
        playlist_control.pause()

    def stop()
        playlist_control.stop()

    def next()
        var was_playing = playing
        if playlist_control.next()
            if was_playing
                play()
        else
            iter: Gtk.TreeIter
            if playlist_store.get_iter_first(out iter)
                playlist_selection.select_iter(iter)

    def on_prev()
        var was_playing = playing
        if playlist_control.prev()
            if was_playing
                play()

    def playlist_control_xid_prepared(imagesink: Gst.XOverlay)
        video_area.sink = imagesink
        notebook.page = Tab.VIDEO

    def on_mute_clicked()
        var volume = volume_button.adjustment
        previous_volume = volume.value
        volume.value = 0
        is_muted = true
        volume_button.get_popup().hide()

    def on_volume_button_pressed(): bool
        if is_muted
            volume_button.adjustment.value = previous_volume
            is_muted = false
            return true
        return false

    def on_notebook_switch_page(num_page: uint)
        if num_page == Tab.VIDEO
            fullscreen_button.show()
        else
            fullscreen_button.hide()

    def new_volume_button_with_mute(): Gtk.VolumeButton
        var volume_button = new Gtk.VolumeButton()
        var icon_size = toolbar.get_icon_size()
        volume_button.size = icon_size

        volume_button.button_press_event += on_volume_button_pressed

        var popup_window = volume_button.get_popup() as Gtk.Window
        popup_window.height_request = 240

        var popup_frame = popup_window.child as Gtk.Frame
        var popup_box = popup_frame.child as Gtk.Box
        popup_box.spacing = 24
        popup_box.remove(volume_button.get_plus_button())
        popup_box.remove(volume_button.get_minus_button())

        var mute_button = new Gtk.Button()
        popup_box.pack_end(mute_button, false, false, 0)
        muted_icon_name = volume_button.icons[0]
        mute_image = new Gtk.Image.from_icon_name(muted_icon_name, icon_size)
        mute_button.add(mute_image)
        mute_button.clicked += on_mute_clicked
        mute_button.realize()

        volume_adjustment = new Gtk.Adjustment(0, 0, 1.0, 0.1, 0.1, 0)
        volume_button.adjustment = volume_adjustment
        volume_adjustment.value_changed += def(volume)
            playlist_control.volume = volume.value
        volume_adjustment.value = playlist_control.volume

        return volume_button

    def new_playlist_box(): Gtk.Box
        var box = new Gtk.VBox(false, 0)

        var scrolled_window = new Gtk.ScrolledWindow(null, null)
        box.pack_start(scrolled_window, true, true, 0)
        var policy = Gtk.PolicyType.AUTOMATIC
        scrolled_window.set_policy(policy, policy)

        playlist_view = new_playlist_view()
        scrolled_window.add(playlist_view)
        playlist_view.model = playlist_store
        playlist_selection = playlist_view.get_selection()
        playlist_selection.set_mode(Gtk.SelectionMode.BROWSE)

        return box

    def new_video_box(): Gtk.Box
        var box = new Gtk.VBox(false, 0)
        video_area = new Omap.VideoArea()
        box.pack_start(video_area, true, true, 0)
        video_area.activated += toggle_fullscreen
        return box

    def new_playlist_view(): Gtk.TreeView
        var view = new Gtk.TreeView()
        view.headers_visible = false
        view.row_activated += on_row_activated

        view.insert_column_with_attributes(
            -1, "Icon", new Gtk.CellRendererPixbuf(),
            "stock-id", playlist_control.get_icon_column(),
            null)
        view.insert_column_with_attributes(
            -1, "Title", new Gtk.CellRendererText(),
            "markup", playlist_control.get_title_column(),
            null)
        view.insert_column_with_attributes(
            -1, "Artist", new Gtk.CellRendererText(),
            "markup", playlist_control.get_artist_column(),
            null)
        view.insert_column_with_attributes(
            -1, "Album", new Gtk.CellRendererText(),
            "markup", playlist_control.get_album_column(),
            null)

        for var column in view.get_columns()
            column.sizing = Gtk.TreeViewColumnSizing.AUTOSIZE

        return view

    def get_and_select_iter(out iter: Gtk.TreeIter): bool
        if not playlist_selection.get_selected(null, out iter)
            if not playlist_control.get_iter(out iter)
                if not playlist_store.get_iter_first(out iter)
                    return false
        var path = playlist_store.get_path(iter)
        playlist_control.move_to(path)
        return true

    def play_pause()
        iter: Gtk.TreeIter
        case playlist_control.state
            when Gst.State.PLAYING
                pause()
            when Gst.State.PAUSED
                play()
            when Gst.State.NULL
                if not get_and_select_iter(out iter)
                    return
                var row = playlist_store.get_path(iter)
                playlist_control.move_to(row)
                notebook.page = Tab.LIST
                play()

    def playlist_control_playing(iter: Gtk.TreeIter)
        title = playlist_control.iter_get_title(iter)
        play_pause_button.stock_id = Gtk.STOCK_MEDIA_PAUSE
        add_update_scale_timeout()
        seeking_scale.show()

    def playlist_control_paused(iter: Gtk.TreeIter)
        play_pause_button.stock_id = Gtk.STOCK_MEDIA_PLAY
        remove_update_scale_timeout()

    def playlist_control_stopped(iter: Gtk.TreeIter)
        title = TITLE
        var page = notebook.page
        if page != Tab.LIST
            notebook.page = Tab.LIST
        play_pause_button.stock_id = Gtk.STOCK_MEDIA_PLAY
        remove_update_scale_timeout()
        seeking_scale.hide()

    def playlist_control_moved(iter: Gtk.TreeIter)
        playlist_selection.select_iter(iter)

    def on_add()
        iter: Gtk.TreeIter
        setup_chooser()
        chooser.show()
        chooser.run()
        get_and_select_iter(out iter)

    def setup_chooser()
        if chooser != null
            return
        chooser = new Gtk.FileChooserDialog(
            "Add files to playlist",
            this,
            Gtk.FileChooserAction.OPEN,
            Gtk.STOCK_CLOSE, Gtk.ResponseType.CLOSE,
            Gtk.STOCK_ADD, Gtk.ResponseType.OK,
            null)
        chooser.response += on_chooser_response

    def on_chooser_response(response: int)
        case response
            when Gtk. ResponseType.CLOSE
                chooser.hide()
            when Gtk.ResponseType.OK
                playlist_control.add_file(chooser.get_filename())

    def on_remove()
        on_remove_files()
        iter: Gtk.TreeIter
        get_and_select_iter(out iter)

    def on_remove_files()
        iter: Gtk.TreeIter
        for row in playlist_selection.get_selected_rows(null)
            playlist_store.get_iter(out iter, row)
            playlist_store.remove(iter)

    def on_row_activated(row: Gtk.TreePath)
        stop()
        if playlist_control.move_to(row)
            play()

    def on_seeking_scale_pressed(): bool
        if playing
            pause()
            should_resume_playback = true
        else
            should_resume_playback = false
        return false

    def on_seeking_scale_released(): bool
        real_value: int64
        real_value = (int64)(seeking_adjustment.value * stream_duration/100)
        playlist_control.position = real_value
        if should_resume_playback
            play()
        return false

    def on_scale_format_value(scale_value: double): string
        real_value: double
        real_duration: double

        if stream_duration == -1
            real_value = 0
            real_duration = 0
        else
            real_value = scale_value * stream_duration / 100.0
            real_duration = stream_duration

        sec0: int = (int)(real_value / Gst.SECOND)
        sec1: int = (int)(real_duration / Gst.SECOND)
        return "%02d:%02d/%02d:%02d".printf(sec0/60, sec0%60, sec1/60, sec1%60)

    def add_update_scale_timeout()
        if update_seeking_scale_id != 0
            return
        var timeout_id = Timeout.add(500, update_scale_timeout)
        update_seeking_scale_id = timeout_id

    def remove_update_scale_timeout()
        if update_seeking_scale_id == 0
            return
        Source.remove(update_seeking_scale_id)
        update_seeking_scale_id = 0

    def update_scale_timeout(): bool
        stream_position = playlist_control.position
        stream_duration = playlist_control.duration

        if stream_position >= 0 and stream_duration > 0
            var stream_value = stream_position * 100.0 / stream_duration
            seeking_adjustment.value = stream_value
        return true

    def setup_debug_dialog()
        if debug_dialog != null
            return
        seeking_scale.hide()
        toolbar.hide()
        debug_dialog = new Omap.DebugDialog(this)
        debug_dialog.closed += on_debug_dialog_closed
        debug_dialog.show()

    def on_debug_dialog_closed()
        toolbar.show()
        stop()
        debug_dialog = null

    def playlist_control_eos(src: Gst.Object)
        next_button.activate()

    def playlist_control_error(src: Gst.Object, error: Error, debug: string)
        setup_debug_dialog()
        debug_dialog.add_error_debug(error, debug)

