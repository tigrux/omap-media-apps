[indent=4]

uses Gtk


const TITLE: string = "Omap4 ImageView"


class ImageViewWindow: MediaWindow
    chooser_button: FileChooserButton
    icon_view: IconView
    video_area: VideoArea
    iconlist_store: ListStore
    iconlist_control: IconListControl
    image_control: ImageControl
    current_folder: string
    image_button: ToolButton
    slideshow_button: ToolButton
    fullscreen_button: ToolButton
    slideshow_timeout: uint
    slideshow_continuation: SourceFunc
    slideshow_cancellable: Cancellable

    is_filling_icons: bool
    fill_icons_continuation: SourceFunc
    fill_icons_cancellable: Cancellable

    init
        setup_model()
        setup_widgets()

    final
        if iconlist_control != null
            iconlist_control.files_added.disconnect(on_iconlist_files_added)

    construct() raises Error
        setup_controls()

    def setup_model()
        iconlist_store = IconListControl.model_new()

    def setup_controls() raises Error
        iconlist_control = new IconListControl(iconlist_store)
        iconlist_control.files_added += on_iconlist_files_added
        iconlist_control.icons_filled += on_iconlist_icons_filled
        image_control = new ImageControl()
        image_control.eos_message += on_image_control_eos
        image_control.prepare_xwindow_id += on_xid_prepared

    def setup_widgets()
        title = TITLE
        setup_toolbar()
        setup_notebook()
        video_area.realize()
        main_box.show_all()

    def setup_notebook()
        notebook.append_page(new_iconlist_box(), new Label("List"))
        notebook.append_page(new_video_box(), new Label("Video"))
        notebook.switch_page += def(page, num_page)
            on_notebook_switch_page(num_page)

    def new_iconlist_box(): Box
        var box = new VBox(false, 0)
        var scrolled_window = new ScrolledWindow(null, null)
        box.pack_start(scrolled_window, true, true, 0)
        scrolled_window.set_policy(PolicyType.AUTOMATIC, PolicyType.AUTOMATIC)

        adjustment: Adjustment

        adjustment = scrolled_window.vadjustment
        adjustment.value_changed += do_fill_visible_icons

        adjustment = scrolled_window.hadjustment
        adjustment.value_changed += do_fill_visible_icons

        icon_view = new IconView()
        scrolled_window.add(icon_view)
        icon_view.size_request += do_fill_visible_icons
        icon_view.selection_mode = SelectionMode.BROWSE
        icon_view.model = iconlist_store
        icon_view.text_column = iconlist_control.get_text_column()
        icon_view.pixbuf_column = iconlist_control.get_pixbuf_column()
        icon_view.row_spacing = 0
        icon_view.column_spacing = 0
        icon_view.spacing = 0
        icon_view.margin = 0
        icon_view.item_activated += on_icon_activated

        return box

    def on_icon_activated(path: TreePath)
        iter: TreeIter
        iconlist_store.get_iter(out iter, path)
        if iconlist_control.iter_is_valid(iter)
            width, height: int
            iconlist_control.iter_get_size(iter, out width, out height)
            video_area.set_size_request(width, height)
            var file = iconlist_control.iter_get_file(iter)
            image_control.location = file
            image_control.state = Gst.State.PLAYING

    def on_xid_prepared(imagesink: Gst.XOverlay)
        video_area.sink = imagesink

    def new_video_box(): Box
        var box = new VBox(false, 0)
        var scrolled_window = new ScrolledWindow(null, null)
        scrolled_window.set_policy(PolicyType.AUTOMATIC, PolicyType.AUTOMATIC)
        box.pack_start(scrolled_window, true, true, 0)
        video_area = new VideoArea()
        video_area.activated += toggle_fullscreen
        scrolled_window.add_with_viewport(video_area)
        return box

    def setup_toolbar()
        var chooser_item = new ToolItem()
        chooser_item.set_expand(true)
        toolbar.add(chooser_item)

        chooser_button = new FileChooserButton( \
            "Select folder", FileChooserAction.SELECT_FOLDER)
        chooser_item.add(chooser_button)
        chooser_button.current_folder_changed += on_chooser_folder_changed

        toolbar_add_expander()

        image_button = new ToolButton.from_stock(STOCK_ZOOM_100)
        toolbar.add(image_button)
        image_button.clicked += on_open_close

        toolbar_add_expander()

        slideshow_button = new ToolButton.from_stock(STOCK_MEDIA_PLAY)
        toolbar.add(slideshow_button)
        slideshow_button.clicked += on_slideshow

        toolbar_add_expander()

        fullscreen_button = new ToolButton.from_stock(STOCK_FULLSCREEN)
        toolbar.add(fullscreen_button)
        fullscreen_button.clicked += on_fullscreen

        toolbar_add_quit_button()

    def on_open_close()
        if notebook.page == Tab.LIST
            open_image()
        else
            close_image()

    def open_image(): bool
        iter: TreeIter
        if get_and_select_iter(out iter)
            icon_view.item_activated(iconlist_store.get_path(iter))
            return true
        return false

    def close_image()
        if slideshow_cancellable != null
            stop_slideshow()
        notebook.page = Tab.LIST

    def on_slideshow()
        iter: TreeIter
        if not iconlist_store.get_iter_first(out iter)            
            return
        else if slideshow_continuation == null
            start_slideshow()
        else
            stop_slideshow()

    def on_notebook_switch_page(num_page: uint)
        if num_page == Tab.LIST
            image_button.stock_id = STOCK_ZOOM_100
        else
            image_button.stock_id = STOCK_CLOSE

    def on_fullscreen()
        if notebook.page == Tab.VIDEO
            toggle_fullscreen()
        else
            if open_image()
                toggle_fullscreen()          

    def start_slideshow()
        slideshow_cancellable = new Cancellable()
        slideshow()
        slideshow_button.stock_id = STOCK_MEDIA_STOP

    def stop_slideshow()
        slideshow_cancellable.cancel()
        if slideshow_timeout != 0
            Source.remove(slideshow_timeout)
            Idle.add(slideshow_continuation)
            slideshow_button.stock_id = STOCK_MEDIA_PLAY

    def on_image_control_eos()
        image_control.state = Gst.State.READY
        notebook.page = Tab.VIDEO
        if slideshow_continuation != null
            slideshow_timeout = Timeout.add_seconds(2, slideshow_continuation)

    def async slideshow()
        iter: TreeIter
        if not get_and_select_iter(out iter) \
           or slideshow_cancellable.is_cancelled()
            return
        slideshow_continuation = slideshow.callback
        do
            var path = iconlist_store.get_path(iter)
            if not iconlist_control.iter_is_valid(iter)
                continue
            icon_view.select_path(path)
            icon_view.scroll_to_path(path, true, 0.5f, 0.5f)
            icon_view.item_activated(path)
            yield
            slideshow_timeout = 0
        while iconlist_store.iter_next(ref iter) \
              and not slideshow_cancellable.is_cancelled()
        if not slideshow_cancellable.is_cancelled()
            close_image()
        slideshow_button.stock_id = STOCK_MEDIA_PLAY
        slideshow_continuation = null
        slideshow_cancellable = null

    def get_and_select_iter(out iter: TreeIter): bool
        path: TreePath
        selected: unowned List of TreePath = icon_view.get_selected_items()
        if selected != null
            path = selected.data
            iconlist_store.get_iter(out iter, path)
            return true
        else
            if iconlist_store.get_iter_first(out iter)
                path = iconlist_store.get_path(iter)
                icon_view.select_path(path)
                return true
        return false

    def on_chooser_folder_changed()
        var folder = chooser_button.get_filename()
        if folder == current_folder
            return
        current_folder = folder
        change_folder()

    def change_folder()
        if fill_icons_cancellable == null
            iconlist_store.clear()
            fill_icons_cancellable = new Cancellable()
            iconlist_control.add_folder(current_folder, fill_icons_cancellable)
        else
            fill_icons_cancellable.cancel()
            Idle.add(retry_change_folder)

    def retry_change_folder(): bool
        if fill_icons_cancellable == null
            change_folder()
            return false
        return true

    def on_iconlist_files_added()
        if fill_icons_cancellable != null
            Idle.add(fill_visible_icons)

    def do_fill_visible_icons()
        if fill_icons_cancellable == null
            fill_icons_cancellable = new Cancellable()
            fill_visible_icons()
        else
            if is_filling_icons
                fill_icons_cancellable.cancel()
            Idle.add(retry_do_fill_visible_icons)

    def retry_do_fill_visible_icons(): bool
        if fill_icons_cancellable == null
            do_fill_visible_icons()
            return false
        return true

    def fill_visible_icons(): bool
        start: TreePath
        end: TreePath
        icon_view.get_visible_range(out start, out end)
        is_filling_icons = true
        iconlist_control.fill_icons(start, end, fill_icons_cancellable)
        return false

    def on_iconlist_icons_filled()
        fill_icons_cancellable = null
        is_filling_icons = false

