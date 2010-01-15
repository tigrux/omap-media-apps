[indent=4]

uses Gtk


enum ImageListCol
    TEXT
    FILE
    PIXBUF


class ImageViewWindow: Window
    chooser_button: FileChooserButton
    icon_view: IconView
    iconlist_store: ListStore
    iconlist_control: IconListControl

    init
        iconlist_store = new_imagelist_store()
        setup_widgets()
    
    construct() raises Error
        iconlist_control = new IconListControl(iconlist_store)

    def setup_widgets()
        set_default_size(DEFAULT_WIDTH, DEFAULT_HEIGHT)
        destroy += Gtk.main_quit

        var main_box = new VBox(false, 6)
        add(main_box)

        var buttons_box = new HBox(false, 6)
        main_box.pack_start(buttons_box, false, false, 0)

        chooser_button = new FileChooserButton( \
            "Select folder", FileChooserAction.SELECT_FOLDER)
        buttons_box.pack_start(chooser_button, true, true, 0)
        chooser_button.current_folder_changed += on_chooser_folder_changed
        
        var scrolled_window = new ScrolledWindow(null, null)
        main_box.pack_start(scrolled_window, true, true, 0)
        scrolled_window.set_policy(PolicyType.AUTOMATIC, PolicyType.AUTOMATIC)
        
        icon_view = new IconView()
        scrolled_window.add(icon_view)
        icon_view.set_model(iconlist_store)
        icon_view.set_text_column(ImageListCol.TEXT)
        icon_view.set_pixbuf_column(ImageListCol.PIXBUF)

        main_box.show_all()

    def on_chooser_folder_changed()
        var folder = chooser_button.get_filename()
        iconlist_store.clear()
        iconlist_control.add_folder(folder)

    def new_imagelist_store(): ListStore
        var s = typeof(string)
        var p = typeof(Gdk.Pixbuf)
        var model = new ListStore(3, s, s, p)
        return model

