[indent=4]

uses Gtk

const TITLE: string = "ImageViewApp"


class ImageViewWindow: ApplicationWindow
    chooser_button: FileChooserButton
    icon_view: IconView
    video_area: VideoArea
    iconlist_store: ListStore
    iconlist_control: IconListControl
    image_control: ImageControl
    cancellable: Cancellable
    current_folder: string
    open_button: ToolButton
    play_button: ToolButton
    is_filling_icons: bool

    init
        iconlist_store = new_imagelist_store()
        setup_widgets()

    final
        if iconlist_control != null
            iconlist_control.files_added.disconnect(on_iconlist_files_added)

    construct() raises Error
        iconlist_control = new IconListControl(iconlist_store)
        iconlist_control.files_added += on_iconlist_files_added
        iconlist_control.icons_filled += on_iconlist_icons_filled
        image_control = new ImageControl()
        video_area.set_control(image_control)

    def setup_widgets()
        set_title(TITLE)
        setup_toolbar()
        setup_notebook()
        video_area.realize()
        main_box.show_all()

    def setup_notebook()
        notebook.append_page(new_iconlist_box(), new Label("List"))
        notebook.append_page(new_video_box(), new Label("Video"))

    def new_iconlist_box(): Box
        var box = new VBox(false, 0)
        var scrolled_window = new ScrolledWindow(null, null)
        box.pack_start(scrolled_window, true, true, 0)
        scrolled_window.set_policy(PolicyType.AUTOMATIC, PolicyType.AUTOMATIC)
        
        adjustment: Adjustment

        adjustment = scrolled_window.get_vadjustment()
        adjustment.value_changed += on_scrolled

        adjustment = scrolled_window.get_hadjustment()
        adjustment.value_changed += on_scrolled
        
        icon_view = new IconView()
        scrolled_window.add(icon_view)
        icon_view.set_selection_mode(SelectionMode.BROWSE)
        icon_view.set_model(iconlist_store)
        icon_view.set_text_column(iconlist_control.get_text_column())
        icon_view.set_pixbuf_column(iconlist_control.get_pixbuf_column())
        icon_view.set_row_spacing(0)
        icon_view.set_column_spacing(0)
        icon_view.set_spacing(0)
        icon_view.set_margin(0)
        icon_view.item_activated += on_icon_activated
        
        return box

    def on_icon_activated(path: TreePath)
        iter: TreeIter
        iconlist_store.get_iter(out iter, path)
        if iconlist_control.iter_is_valid(iter)
            var file = iconlist_control.iter_get_file(iter)
            image_control.location = file
            image_control.set_state(Gst.State.PLAYING)

    def new_video_box(): Box
        var box = new VBox(false, 0)
        var scrolled_window = new ScrolledWindow(null, null)
        scrolled_window.set_policy(PolicyType.AUTOMATIC, PolicyType.AUTOMATIC)
        box.pack_start(scrolled_window, true, true, 0)
        video_area = new VideoArea()
        scrolled_window.add_with_viewport(video_area)
        video_area.prepared += on_video_area_prepared
        return box

    def on_video_area_prepared()
        notebook.set_current_page(ApplicationTab.VIDEO)
        open_button.set_stock_id(STOCK_CLOSE)

    def setup_toolbar()
        var chooser_item = new ToolItem()
        chooser_item.set_expand(true)
        toolbar.add(chooser_item)

        chooser_button = new FileChooserButton( \
            "Select folder", FileChooserAction.SELECT_FOLDER)
        chooser_item.add(chooser_button)
        chooser_button.set_create_folders(false)
        chooser_button.current_folder_changed += on_chooser_folder_changed

        toolbar_add_expander()

        open_button = new ToolButton.from_stock(STOCK_OPEN)
        toolbar.add(open_button)
        open_button.clicked += on_open

        play_button = new ToolButton.from_stock(STOCK_MEDIA_PLAY)
        toolbar.add(play_button)
        play_button.clicked += on_play

        toolbar_add_quit_button()

    def on_open()
        if notebook.get_current_page() == ApplicationTab.LIST
            iter: TreeIter
            if get_and_select_iter(out iter)
                icon_view.item_activated(iconlist_store.get_path(iter))
        else
            image_control.set_state(Gst.State.NULL)
            notebook.set_current_page(ApplicationTab.LIST)
            open_button.set_stock_id(STOCK_OPEN)

    def on_play()
        print "Start slideshow"

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
        var folder = chooser_button.get_current_folder()
        if folder == current_folder
            return
        current_folder = folder
        change_folder()

    def change_folder()
        if cancellable == null
            iconlist_store.clear()
            cancellable = new Cancellable()
            iconlist_control.add_folder(current_folder, cancellable)
        else
            cancellable.cancel()
            Idle.add(retry_change_folder)
    
    def retry_change_folder(): bool
        if cancellable == null
            change_folder()
            return false
        return true

    def on_iconlist_files_added()
        if cancellable != null
            Idle.add(fill_visible_icons)

    def on_scrolled()
        if cancellable == null
            cancellable = new Cancellable()
            fill_visible_icons()
        else
            if is_filling_icons
                cancellable.cancel()
            Idle.add(retry_on_scrolled)

    def retry_on_scrolled(): bool
        if cancellable == null
            on_scrolled()
            return false
        return true

    def fill_visible_icons(): bool
        start: TreePath
        end: TreePath
        icon_view.get_visible_range(out start, out end)
        is_filling_icons = true
        iconlist_control.fill_icons(start, end, cancellable)
        return false

    def on_iconlist_icons_filled()
        cancellable = null
        is_filling_icons = false

    def new_imagelist_store(): ListStore
        var s = typeof(string)
        var p = typeof(Gdk.Pixbuf)
        var b = typeof(bool)
        var model = new ListStore(5, s, s, p, b, b)
        return model

