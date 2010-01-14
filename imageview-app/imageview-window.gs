[indent=4]

uses Gtk
uses Gst

const PIXBUF_PIPELINE_DESC: string = """
filesrc name=filesrc ! jpegdec ! ffmpegcolorspace ! videoscale !
video/x-raw-rgb,width=128,height=96 ! gdkpixbufsink name=imagesink
"""

const IMAGE_FILE_ATTRIBUTES: string = "standard::name,standard::display-name,standard::content-type"

enum ImageListCol
    TEXT
    FILE
    PIXBUF

delegate bus_callback(message: Gst.Message)

class ImageViewWindow: Window
    icon_view: IconView
    imagelist_store: ListStore
    chooser_button: FileChooserButton

    pipeline: Pipeline
    filesrc: dynamic Element
    imagesink: dynamic Element

    continuation: SourceFunc
    continuation_error: Error

    init
        imagelist_store = new_imagelist_store()
        setup_elements()
        setup_widgets()
        pass

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
        icon_view.set_model(imagelist_store)
        icon_view.set_text_column(ImageListCol.TEXT)
        icon_view.set_pixbuf_column(ImageListCol.PIXBUF)

        main_box.show_all()

    def setup_elements()
        try
            pipeline = parse_launch(PIXBUF_PIPELINE_DESC) as Pipeline
        except e: Error
            print e.message
            return
        var bus = pipeline.bus
        bus.add_signal_watch()
        bus.message += on_bus_message
        filesrc = pipeline.get_by_name("filesrc")
        imagesink = pipeline.get_by_name("imagesink")

    def on_chooser_folder_changed()
        var folder = chooser_button.get_filename()
        imagelist_store.clear()
        imagelist_fill_from_dir(folder)

    def async imagelist_fill_from_dir(dirname: string)
        var dir = File.new_for_path (dirname)
        try
            var file_etor = yield dir.enumerate_children_async(\
                                    IMAGE_FILE_ATTRIBUTES, \
                                    FileQueryInfoFlags.NONE, \
                                    Priority.DEFAULT, null)
            while true
                var files = yield file_etor.next_files_async(\
                                    5, Priority.DEFAULT, null)
                if files == null
                    break
                for info in files
                    if info.get_content_type() == "image/jpeg"
                        var file = Path.build_filename(dirname, info.get_name())
                        var display = info.get_display_name()
                        try
                            yield imagelist_add_file(file, display)
                        except e2: Error
                            print e2.message
        except e1: Error
            print e1.message

    def on_bus_message(message: Gst.Message)
        case message.type
            when Gst.MessageType.ERROR
                message.parse_error(out continuation_error, null)
                Idle.add(continuation)
            when Gst.MessageType.EOS
                Idle.add(continuation)
            default
                pass

    def async imagelist_add_file(filename: string, displayname: string) raises Error
        continuation = imagelist_add_file.callback
        filesrc.location = filename
        pipeline.set_state(State.PLAYING)
        yield

        if continuation_error == null
            pixbuf: Gdk.Pixbuf = imagesink.last_pixbuf
            if pixbuf != null
                imagelist_store.insert_with_values(null, -1, \
                    ImageListCol.TEXT, displayname, \
                    ImageListCol.FILE, filename, \
                    ImageListCol.PIXBUF, pixbuf)
        else
            error: Error = (owned)continuation_error
            raise error
        pipeline.set_state(State.NULL)

    def new_imagelist_store(): ListStore
        var s = typeof(string)
        var p = typeof(Gdk.Pixbuf)
        var model = new ListStore(3, s, s, p)
        return model

