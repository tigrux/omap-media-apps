[indent=4]

uses Gtk


const TITLE: string = "Omap4 Player"
const ICON: string = "omap4-player-app"


class PlayerWindow: MediaWindow
    playlist_view: TreeView
    playlist_store: ListStore
    playlist_selection: TreeSelection
    playlist_control: PlayListControl

    play_pause_button: ToolButton
    add_button: ToolButton
    next_button: ToolButton
    fullscreen_button: ToolButton
    remove_image: Gtk.Image
    video_area: VideoArea
    seeking_scale: Scale
    seeking_adjustment: Adjustment
    volume_button: VolumeButton
    volume_adjustment: Adjustment
    mute_image: Image
    previous_volume: double
    muted_icon_name: string
    is_muted: bool
    chooser: FileChooserDialog

    update_seeking_scale_id: uint
    stream_position: int64
    stream_duration: int64
    should_resume_playback: bool

    debug_dialog: DebugDialog

    init
        setup_model()
        setup_controls()
        setup_widgets()

    def setup_model()
        var s = typeof(string)
        playlist_store = new ListStore(3, s, s, s)

    def setup_controls()
        playlist_control = new PlayListControl(playlist_store)
        playlist_control.eos_message += playlist_control_eos
        playlist_control.error_message += playlist_control_error
        playlist_control.playing += playlist_control_playing
        playlist_control.paused += playlist_control_paused
        playlist_control.stopped += playlist_control_stopped
        playlist_control.moved += playlist_control_moved
        playlist_control.prepare_xwindow_id += on_xid_prepared

    def setup_widgets()
        set_title(TITLE)
        lookup_and_set_icon_name(ICON)
        setup_toolbar()
        setup_notebook()
        setup_seeking()
        video_area.realize()
        main_box.show_all()

    def setup_notebook()
        notebook.append_page(new_playlist_box(), new Label("List"))
        notebook.append_page(new_video_box(), new Label("Video"))
        notebook.switch_page += on_notebook_switch_page

    def setup_toolbar()
        var prev_button = new ToolButton.from_stock(STOCK_MEDIA_PREVIOUS)
        prev_button.clicked += on_prev
        toolbar.add(prev_button)

        play_pause_button = new ToolButton.from_stock(STOCK_MEDIA_PLAY)
        toolbar.add(play_pause_button)
        play_pause_button.clicked += play_pause

        next_button = new ToolButton.from_stock(STOCK_MEDIA_NEXT)
        toolbar.add(next_button)
        next_button.clicked += next

        var stop_button = new ToolButton.from_stock(STOCK_MEDIA_STOP)
        toolbar.add(stop_button)
        stop_button.clicked += stop

        toolbar_add_expander()

        var volume_button_item = new ToolItem()
        toolbar.add(volume_button_item)
        volume_button = new_volume_button_with_mute()
        volume_button_item.add(volume_button)

        fullscreen_button = new ToolButton.from_stock(STOCK_FULLSCREEN)
        fullscreen_button.set_no_show_all(true)
        fullscreen_button.clicked += toggle_fullscreen
        toolbar.add(fullscreen_button)

        toolbar_add_expander()

        add_button = new ToolButton.from_stock(STOCK_ADD)
        toolbar.add(add_button)
        add_button.clicked += on_add

        var remove_button = new ToolButton.from_stock(STOCK_REMOVE)
        toolbar.add(remove_button)
        remove_button.clicked += on_remove

        toolbar_add_quit_button()

    def setup_seeking()
        seeking_adjustment = new Adjustment(0, 0, 100, 0.1, 1, 1)
        seeking_scale = new HScale(seeking_adjustment)
        main_box.pack_start(seeking_scale, false, false, 0)

        seeking_scale.set_no_show_all(true)
        seeking_scale.set_update_policy(UpdateType.DISCONTINUOUS)
        seeking_scale.button_press_event += on_seeking_scale_pressed
        seeking_scale.button_release_event += on_seeking_scale_released
        seeking_scale.format_value += on_scale_format_value

    def is_playing(): bool
        return playlist_control.state == Gst.State.PLAYING

    def play()
        playlist_control.play()

    def pause()
        playlist_control.pause()

    def stop()
        playlist_control.stop()

    def next()
        var was_playing = is_playing()
        if playlist_control.next()
            if was_playing
                play()
        else
            iter: TreeIter
            if playlist_store.get_iter_first(out iter)
                playlist_selection.select_iter(iter)

    def on_prev()
        var was_playing = is_playing()
        if playlist_control.prev()
            if was_playing
                play()

    def on_xid_prepared(imagesink: Gst.XOverlay)
        video_area.sink = imagesink
        notebook.set_current_page(Tab.VIDEO)

    def on_mute_clicked()
        var volume = volume_button.get_adjustment()
        previous_volume = volume.get_value()
        volume.set_value(0)
        is_muted = true
        volume_button.get_popup().hide()

    def on_volume_button_pressed(): bool
        if is_muted
            var volume = volume_button.get_adjustment()
            volume.set_value(previous_volume)
            is_muted = false
            return true
        return false

    def on_notebook_switch_page(page: void*, num_page: uint)
        if num_page == Tab.VIDEO
            fullscreen_button.show()
        else
            fullscreen_button.hide()

    def new_volume_button_with_mute(): VolumeButton
        var volume_button = new VolumeButton()
        var icon_size = toolbar.get_icon_size()
        volume_button.size = icon_size

        volume_button.button_press_event += on_volume_button_pressed

        var popup_window = volume_button.get_popup() as Window
        popup_window.set_size_request(-1, 240)

        var popup_frame = popup_window.get_child() as Frame
        var popup_box = popup_frame.get_child() as Box
        popup_box.set_spacing(24)
        popup_box.remove(volume_button.get_plus_button())
        popup_box.remove(volume_button.get_minus_button())

        var mute_button = new Button()
        popup_box.pack_end(mute_button, false, false, 0)
        muted_icon_name = volume_button.icons[0]
        mute_image = new Image.from_icon_name(muted_icon_name, icon_size)
        mute_button.add(mute_image)
        mute_button.clicked += on_mute_clicked
        mute_button.realize()

        volume_adjustment = new Adjustment(0, 0, 1.0, 0.1, 0.1, 0)
        volume_button.set_adjustment(volume_adjustment)
        volume_adjustment.value_changed += def(volume)
            playlist_control.volume = volume.get_value()
        volume_adjustment.set_value(playlist_control.volume)

        return volume_button

    def new_playlist_box(): Box
        var box = new VBox(false, 0)

        var scrolled_window = new ScrolledWindow(null, null)
        box.pack_start(scrolled_window, true, true, 0)
        scrolled_window.set_policy(PolicyType.AUTOMATIC, PolicyType.AUTOMATIC)

        playlist_view = new_playlist_view()
        scrolled_window.add(playlist_view)
        playlist_view.set_model(playlist_store)
        playlist_selection = playlist_view.get_selection()
        playlist_selection.set_mode(SelectionMode.BROWSE)

        return box

    def new_video_box(): Box
        var box = new VBox(false, 0)
        video_area = new VideoArea()
        box.pack_start(video_area, true, true, 0)
        video_area.activated += toggle_fullscreen
        return box

    def new_playlist_view(): TreeView
        var view = new TreeView()
        view.set_headers_visible(false)
        view.row_activated += on_row_activated

        view.insert_column_with_attributes( \
            -1, "Icon", new CellRendererPixbuf(), \
            "stock-id", playlist_control.get_icon_column(), null)

        view.insert_column_with_attributes( \
            -1, "Song", new CellRendererText(), \
            "markup", playlist_control.get_name_column(), null)

        return view

    def get_and_select_iter(out iter: TreeIter): bool
        if not playlist_selection.get_selected(null, out iter)
            if not playlist_control.get_iter(out iter)
                if not playlist_store.get_iter_first(out iter)
                    return false
        var path = playlist_store.get_path(iter)
        playlist_control.move_to(path)
        return true

    def play_pause()
        iter: TreeIter
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
                notebook.set_current_page(Tab.LIST)
                play()

    def playlist_control_playing(iter: TreeIter)
        set_title(playlist_control.iter_get_name(iter))
        play_pause_button.set_stock_id(STOCK_MEDIA_PAUSE)
        add_update_scale_timeout()
        seeking_scale.show()

    def playlist_control_paused(iter: TreeIter)
        play_pause_button.set_stock_id(STOCK_MEDIA_PLAY)
        remove_update_scale_timeout()

    def playlist_control_stopped(iter: TreeIter)
        set_title(TITLE)
        var page = notebook.get_current_page()
        if page != Tab.LIST
            notebook.set_current_page(Tab.LIST)
        play_pause_button.set_stock_id(STOCK_MEDIA_PLAY)
        remove_update_scale_timeout()
        seeking_scale.hide()

    def playlist_control_moved(iter: TreeIter)
        playlist_selection.select_iter(iter)

    def on_add()
        iter: TreeIter
        setup_chooser()
        chooser.show()
        chooser.run()
        get_and_select_iter(out iter)

    def setup_chooser()
        if chooser != null
            return
        chooser = new FileChooserDialog( \
            "Add files to playlist", \
            this, \
            FileChooserAction.OPEN, \
            STOCK_CLOSE, ResponseType.CLOSE, \
            STOCK_ADD, ResponseType.OK, \
            null)
        chooser.response += on_chooser_response

    def on_chooser_response(response: int)
        case response
            when ResponseType.CLOSE
                chooser.hide()
            when ResponseType.OK
                playlist_control.add_file(chooser.get_filename())

    def on_remove()
        on_remove_files()
        iter: TreeIter
        get_and_select_iter(out iter)

    def on_remove_files()
        iter: TreeIter
        for row in playlist_selection.get_selected_rows(null)
            playlist_store.get_iter(out iter, row)
            playlist_store.remove(iter)

    def on_row_activated(row: TreePath)
        stop()
        if playlist_control.move_to(row)
            play()

    def on_seeking_scale_pressed(): bool
        if is_playing()
            pause()
            should_resume_playback = true
        else
            should_resume_playback = false
        return false

    def on_seeking_scale_released(): bool
        real_value: int64
        real_value = (int64)(seeking_scale.get_value() * stream_duration/100)
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
            seeking_adjustment.set_value(stream_value)
        return true

    def setup_debug_dialog()
        if debug_dialog != null
            return
        seeking_scale.hide()
        toolbar.hide()
        debug_dialog = new DebugDialog(this)
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

