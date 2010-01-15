[indent=4]

uses Gtk
uses Gst


enum PlayListCol
    ICON
    NAME
    FULLNAME

enum PlayerTab
    LIST
    VIDEO
    CHOOSER

const UPDATE_INTERVAL: uint = 200
const TITLE: string = "PlayerApp"


class PlayerWindow: Window
    playlist_view: TreeView
    playlist_store: ListStore
    playlist_selection: TreeSelection
    playlist_control: PlayListControl
    controls_box: Box
    notebook: Notebook
    notebook_previous_page: int
    add_button: Button
    next_button: Button
    play_pause_image: Gtk.Image
    remove_close_image: Gtk.Image
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

    chooser_widget: FileChooserWidget
    chooser_view: TreeView

    update_seeking_scale_id: uint
    stream_position: int64
    stream_duration: int64
    should_resume_playback: bool
    is_fullscreen: bool

    error_dialog: ErrorDialog

    init
        playlist_store = new_playlist_store()
        setup_elements()
        setup_widgets()
        var bus = playlist_control.pipeline.get_bus()
        bus.add_signal_watch()
        bus.message += on_bus_message
        video_area.set_bus(bus)

    def is_playing(): bool
        return playlist_control.get_state() == State.PLAYING

    def on_play()
        playlist_control.play()

    def on_pause()
        playlist_control.pause()

    def on_stop()
        playlist_control.stop()

    def on_next()
        if notebook.get_current_page() == PlayerTab.CHOOSER
            var selection = chooser_view.get_selection()
            iter: TreeIter
            if selection.get_selected(null, out iter)
                var model = chooser_view.get_model()
                if model.iter_next(ref iter)
                    selection.select_iter(iter)
                    var path = model.get_path(iter)
                    chooser_view.scroll_to_cell(path, null, false, 0, 0)
        else
            var was_playing = is_playing()
            if playlist_control.next()
                if was_playing
                    on_play()
            else
                iter: TreeIter
                if playlist_store.get_iter_first(out iter)
                    playlist_selection.select_iter(iter)

    def on_prev()
        if notebook.get_current_page() == PlayerTab.CHOOSER
            iter: TreeIter
            var selection = chooser_view.get_selection()
            if selection.get_selected(null, out iter)
                var model = chooser_view.get_model()
                var path = model.get_path(iter)
                if path.prev()
                    if model.get_iter(out iter, path)
                        selection.select_iter(iter)
                        chooser_view.scroll_to_cell(path, null, false, 0, 0)
        else
            var was_playing = is_playing()
            if playlist_control.prev()
                if was_playing
                    on_play()

    def on_quit()
        Idle.add(on_delete)

    def on_delete(): bool
        main_quit()
        return true

    def setup_elements()
        playlist_control = new PlayListControl(playlist_store)
        playlist_control.playing += on_playlist_control_playing
        playlist_control.paused += on_playlist_control_paused
        playlist_control.stopped += on_playlist_control_stopped
        playlist_control.moved += on_playlist_control_moved

    def setup_widgets()
        set_title(TITLE)
        set_default_size(DEFAULT_WIDTH, DEFAULT_HEIGHT)
        delete_event += on_delete

        var main_box = new VBox(false, 0)
        add(main_box)
        controls_box = new_buttons_box()
        main_box.pack_start(controls_box, false, false, 0)

        notebook = new Notebook()
        main_box.pack_start(notebook, true, true, 0)
        notebook.set_show_tabs(false)
        notebook.append_page(new_playlist_box(), new Label("List"))
        notebook.append_page(new_video_box(), new Label("Video"))
        notebook.append_page(new_chooser_box(), new Label("Chooser"))
        notebook.switch_page += on_notebook_switch_page
        notebook.change_current_page += def(page)
            print "page %d", page
        notebook.show()

        seeking_adjustment = new Adjustment(0, 0, 100, 0.1, 1, 1)
        seeking_scale = new HScale(seeking_adjustment)
        main_box.pack_start(seeking_scale, false, false, 0)
        seeking_scale.button_press_event += on_seeking_scale_pressed
        seeking_scale.button_release_event += on_seeking_scale_released
        seeking_scale.format_value += on_scale_format_value

        main_box.show()
        video_area.realize()

    def new_buttons_box(): ButtonBox
        var buttons_box = new HButtonBox()
        buttons_box.set_layout(ButtonBoxStyle.START)
        buttons_box.set_spacing(5)

        var prev_button = new_button_with_stock_image(STOCK_MEDIA_PREVIOUS)
        var play_pause_button = new_button_with_stock_image(STOCK_MEDIA_PLAY)
        var stop_button = new_button_with_stock_image(STOCK_MEDIA_STOP)
        next_button = new_button_with_stock_image(STOCK_MEDIA_NEXT)
        add_button = new_button_with_stock_image(STOCK_ADD)
        var remove_button = new_button_with_stock_image(STOCK_REMOVE)
        var quit_button = new_button_with_stock_image(STOCK_QUIT)

        play_pause_button.clicked += on_play_pause
        stop_button.clicked += on_stop
        prev_button.clicked += on_prev
        next_button.clicked += on_next
        add_button.clicked += on_add
        remove_button.clicked += on_remove
        quit_button.clicked += on_quit

        buttons: array of Button = { \
            prev_button, \
            play_pause_button, \
            stop_button, \
            next_button, \
            add_button, \
            remove_button, \
            quit_button \
        }

        var i = 0
        for button in buttons
            buttons_box.add(button)
            if i >= 4
                buttons_box.set_child_secondary(button, true)
            i++
        play_pause_image = play_pause_button.child as Gtk.Image
        remove_close_image = remove_button.child as Gtk.Image

        volume_button = new_volume_button_with_mute()
        buttons_box.add(volume_button)

        buttons_box.show_all()
        return buttons_box

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

    def new_volume_button_with_mute(): VolumeButton
        var volume_button = new VolumeButton()

        volume_button.size = ICON_SIZE
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
        mute_image = new Image.from_icon_name(muted_icon_name, ICON_SIZE)
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
        var box = new VBox(false, 6)

        var scrolled_window = new ScrolledWindow(null, null)
        box.pack_start(scrolled_window, true, true, 0)
        scrolled_window.set_policy(PolicyType.AUTOMATIC, PolicyType.AUTOMATIC)

        playlist_view = new_playlist_view()
        scrolled_window.add(playlist_view)
        playlist_view.set_model(playlist_store)
        playlist_selection = playlist_view.get_selection()
        playlist_selection.set_mode(SelectionMode.BROWSE)

        box.show_all()
        return box

    def new_video_box(): Box
        var box = new VBox(false, 6)
        video_area = new VideoArea()
        box.pack_start(video_area, true, true, 0)
        video_area.activated += on_video_area_activated
        video_area.prepared += def()
            notebook.set_current_page(PlayerTab.VIDEO)

        box.show_all()
        return box

    def new_chooser_box(): Box
        var box = new VBox(false, 0)

        chooser_widget = new FileChooserWidget(FileChooserAction.OPEN)
        box.pack_start(chooser_widget, true, true, 0)
        chooser_widget.show()
        chooser_widget.set_select_multiple(false)
        chooser_widget.file_activated += def() add_button.activate()

        indices: array of int
        indices = {0, 0, 2, 1, 0, 0, 0}
        chooser_view = child_widget_at_path(chooser_widget, indices) as TreeView

        var columns = chooser_view.get_columns()
        var first_column = columns.data
        for column in columns
            if column != first_column
                column.set_visible(false)

        box.show()
        return box

    def new_playlist_view(): TreeView
        var view = new TreeView()
        view.set_headers_visible(false)
        view.row_activated += on_row_activated

        view.insert_column_with_attributes(\
            -1, "Icon", new CellRendererPixbuf(), \
            "stock-id", PlayListCol.ICON, null)

        view.insert_column_with_attributes(\
            -1, "Song", new CellRendererText(), \
            "markup", PlayListCol.NAME, null)

        view.show_all()
        return view

    def new_playlist_store(): ListStore
        var s = typeof(string)
        var model = new ListStore(3, s, s, s)
        return model

    def get_and_select_iter(out iter: TreeIter): bool
        if not playlist_selection.get_selected(null, out iter)
            if not playlist_control.get_iter(out iter)
                if not playlist_store.get_iter_first(out iter)
                    return false
        var path = playlist_store.get_path(iter)
        playlist_control.move_to(path)
        return true

    def on_play_pause()
        iter: TreeIter
        case playlist_control.get_state()
            when State.PLAYING
                on_pause()
            when State.PAUSED
                on_play()
            when State.NULL
                if notebook.get_current_page() == PlayerTab.CHOOSER
                    add_file_from_chooser(out iter)
                    if playlist_store.iter_is_valid(iter)
                        playlist_selection.select_iter(iter)
                        if get_and_select_iter(out iter)
                            on_play()
                else
                    if not get_and_select_iter(out iter)
                        return
                    var row = playlist_store.get_path(iter)
                    playlist_control.move_to(row)
                    notebook.set_current_page(PlayerTab.LIST)
                    on_play()

    def on_playlist_control_playing(iter: TreeIter)
        name: string
        playlist_store.get(iter, PlayListCol.NAME, out name, -1)
        set_title(name)
        play_pause_image.set_from_stock(STOCK_MEDIA_PAUSE, ICON_SIZE)
        add_update_scale_timeout()
        seeking_scale.show()

    def on_playlist_control_paused(iter: TreeIter)
        play_pause_image.set_from_stock(STOCK_MEDIA_PLAY, ICON_SIZE)
        remove_update_scale_timeout()

    def on_playlist_control_stopped(iter: TreeIter)
        set_title(TITLE)
        var page = notebook.get_current_page()
        if not (page == PlayerTab.LIST or page == PlayerTab.CHOOSER)
            notebook.set_current_page(PlayerTab.LIST)
        play_pause_image.set_from_stock(STOCK_MEDIA_PLAY, ICON_SIZE)
        remove_update_scale_timeout()
        seeking_scale.hide()

    def on_playlist_control_moved(iter: TreeIter)
        playlist_selection.select_iter(iter)

    def on_add()
        iter: TreeIter
        if notebook.get_current_page() != PlayerTab.CHOOSER
            notebook.set_current_page(PlayerTab.CHOOSER)
        else
            add_file_from_chooser(out iter)
            get_and_select_iter(out iter)

    def add_file_from_chooser(out iter: TreeIter)
        var filename = chooser_widget.get_filename()
        if FileUtils.test(filename, FileTest.IS_DIR)
            chooser_widget.set_current_folder(filename)
        else if FileUtils.test(filename, FileTest.IS_REGULAR)
            playlist_control.add_file(filename, out iter)

    def on_remove()
        if notebook.get_current_page() == PlayerTab.CHOOSER
            notebook.set_current_page(notebook_previous_page)
        else
            on_remove_files()
            iter: TreeIter
            get_and_select_iter(out iter)

    def on_remove_files()
        iter: TreeIter
        for row in playlist_selection.get_selected_rows(null)
            playlist_store.get_iter(out iter, row)
            playlist_store.remove(iter)

    def on_row_activated(row: TreePath)
        on_stop()
        if playlist_control.move_to(row)
            on_play()

    def on_seeking_scale_pressed(): bool
        if is_playing()
            on_pause()
            should_resume_playback = true
        else
            should_resume_playback = false
        return false

    def on_seeking_scale_released(): bool
        real_value: int64
        real_value = (int64)(seeking_scale.get_value() * stream_duration/100)
        playlist_control.seek(real_value)
        if should_resume_playback
            on_play()
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

        sec0: int = (int)(real_value / SECOND)
        sec1: int = (int)(real_duration / SECOND)
        return "%02d:%02d/%02d:%02d".printf(sec0/60, sec0%60, sec1/60, sec1%60)

    def add_update_scale_timeout()
        if update_seeking_scale_id != 0
            return
        var timeout_id = Timeout.add(UPDATE_INTERVAL, update_scale_timeout)
        update_seeking_scale_id = timeout_id

    def remove_update_scale_timeout()
        if update_seeking_scale_id == 0
            return
        Source.remove(update_seeking_scale_id)
        update_seeking_scale_id = 0

    def update_scale_timeout(): bool
        var format = Format.TIME
        var pipeline = playlist_control.pipeline

        pipeline.query_position(ref format, out stream_position)
        pipeline.query_duration(ref format, out stream_duration)

        if stream_position >= 0 and stream_duration > 0
            var stream_value = stream_position * 100.0 / stream_duration
            seeking_adjustment.set_value(stream_value)
        return true

    def on_notebook_switch_page(page: void*, page_num: uint)
        if page_num == PlayerTab.CHOOSER
            remove_close_image.set_from_stock(STOCK_CLOSE, ICON_SIZE)
        else
            remove_close_image.set_from_stock(STOCK_REMOVE, ICON_SIZE)
        notebook_previous_page = notebook.get_current_page()

    def on_video_area_activated()
        if is_fullscreen
            controls_box.show()
            seeking_scale.show()
            unfullscreen()
            activate_default()
            is_fullscreen = false
        else
            controls_box.hide()
            seeking_scale.hide()
            fullscreen()
            is_fullscreen = true
            controls_box.grab_focus()

    def on_bus_message(message: Message)
        case message.type
            when Gst.MessageType.EOS
                next_button.activate()
            when Gst.MessageType.ERROR
                error: Error
                debug: string
                setup_error_dialog()
                message.parse_error(out error, out debug)
                error_dialog.add_error_with_debug(error, debug)
            default
                pass

    def setup_error_dialog()
        if error_dialog == null
            seeking_scale.hide()
            controls_box.hide()
            error_dialog = new ErrorDialog()
            error_dialog.closed += on_error_dialog_closed
            error_dialog.set_transient_for(this)
            error_dialog.show_all()

    def on_error_dialog_closed()
        controls_box.show()
        on_stop()
        error_dialog = null

