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

    init
        iconlist_store = new_imagelist_store()
        setup_widgets()

    final
        if iconlist_control != null
            iconlist_control.done.disconnect(on_iconlist_done)

    construct() raises Error
        iconlist_control = new IconListControl(iconlist_store)
        iconlist_control.done += on_iconlist_done
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
        
        icon_view = new IconView()
        scrolled_window.add(icon_view)
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
        if iconlist_control.iter_get_valid(iter)
            image_control.filesrc.location = iconlist_control.iter_get_file(iter)
            image_control.pipeline.set_state(Gst.State.PLAYING)

    def new_video_box(): Box
        var box = new VBox(false, 0)
        var scrolled_window = new ScrolledWindow(null, null)
        scrolled_window.set_policy(PolicyType.AUTOMATIC, PolicyType.AUTOMATIC)
        box.pack_start(scrolled_window, true, true, 0)
        video_area = new VideoArea()
        scrolled_window.add_with_viewport(video_area)
        video_area.prepared += def()
            notebook.set_current_page(ApplicationTab.VIDEO)
        return box

    def setup_toolbar()
        var chooser_item = new ToolItem()
        chooser_item.set_expand(true)
        toolbar.add(chooser_item)

        chooser_button = new FileChooserButton( \
            "Select folder", FileChooserAction.SELECT_FOLDER)
        chooser_item.add(chooser_button)
        chooser_button.set_create_folders(false)
        chooser_button.current_folder_changed += on_chooser_folder_changed
        
        toolbar_add_quit_button()
        
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

    def on_iconlist_done()
        cancellable = null

    def new_imagelist_store(): ListStore
        var s = typeof(string)
        var p = typeof(Gdk.Pixbuf)
        var b = typeof(bool)
        var model = new ListStore(4, s, s, p, b)
        return model

