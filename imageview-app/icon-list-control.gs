[indent=4]

uses Gst
uses Gtk


const PIXBUF_PIPELINE_DESC: string = """
filesrc name=filesrc ! jpegdec ! ffmpegcolorspace ! videoscale !
video/x-raw-rgb,width=128,height=96 ! gdkpixbufsink name=imagesink
"""

const IMAGE_FILE_ATTRIBUTES: string = "standard::name,standard::display-name,standard::content-type"


class IconListControl: GLib.Object
    pipeline: Pipeline
    filesrc: dynamic Element
    imagesink: dynamic Element
    missing_pixbuf: Gdk.Pixbuf
    loading_pixbuf: Gdk.Pixbuf

    prop iconlist_store: ListStore
    continuation: SourceFunc
    continuation_error: Error

    construct(model: ListStore) raises Error
        iconlist_store = model
        setup_icons()
        setup_elements()

    final
        if pipeline != null
            pipeline.set_state(State.NULL)

    def setup_icons() raises Error
        var icon_theme = IconTheme.get_default()
        icon_info: IconInfo

        icon_info = icon_theme.lookup_icon( \
            STOCK_MISSING_IMAGE, 96, IconLookupFlags.FORCE_SIZE)
        if icon_info != null
            missing_pixbuf = icon_info.load_icon()

        icon_info = icon_theme.lookup_icon( \
            "image-loading", 96, IconLookupFlags.FORCE_SIZE)
        if icon_info != null
            loading_pixbuf = icon_info.load_icon()

        pipeline = parse_launch(PIXBUF_PIPELINE_DESC) as Pipeline
        if (filesrc = pipeline.get_by_name("filesrc")) == null
            raise new CoreError.FAILED( \
                        "No element named filesrc in the pixbuf pipeline")
        if (imagesink = pipeline.get_by_name("imagesink")) == null
            raise new CoreError.FAILED( \
                        "No element named imagesink in the pixbuf pipeline")
        var bus = pipeline.bus
        bus.add_signal_watch()
        bus.message += on_bus_message

    def setup_elements() raises Error
        pipeline = parse_launch(PIXBUF_PIPELINE_DESC) as Pipeline
        if (filesrc = pipeline.get_by_name("filesrc")) == null
            raise new CoreError.FAILED( \
                        "No element named filesrc in the pixbuf pipeline")
        if (imagesink = pipeline.get_by_name("imagesink")) == null
            raise new CoreError.FAILED( \
                        "No element named imagesink in the pixbuf pipeline")
        var bus = pipeline.bus
        bus.add_signal_watch()
        bus.message += on_bus_message

    def async add_file(file: string, text: string)
        iconlist_store.insert_with_values(null, -1, \
            ImageListCol.TEXT, text, \
            ImageListCol.FILE, file, \
            ImageListCol.PIXBUF, loading_pixbuf, \
            -1)

    def async add_folder(dirname: string)
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
                        var text = info.get_display_name()
                        add_file(file, text)
            yield retrieve_icons()
        except e1: Error
            print e1.message

    def async retrieve_icons()
        iter: TreeIter
        if iconlist_store.get_iter_first(out iter)
            continuation = retrieve_icons.callback
            do
                file: string
                display: string
                iconlist_store.get(iter, \
                    ImageListCol.TEXT, out display, \
                    ImageListCol.FILE, out file, \
                    -1)
                filesrc.location = file
                pipeline.set_state(State.PLAYING)
                yield
                if continuation_error == null
                    pixbuf: Gdk.Pixbuf = imagesink.last_pixbuf
                    iconlist_store.set(iter, \
                        ImageListCol.PIXBUF, pixbuf, \
                        -1)
                else
                    continuation_error = null
                pipeline.set_state(State.NULL)
            while iconlist_store.iter_next(ref iter)

    def on_bus_message(message: Gst.Message)
        case message.type
            when Gst.MessageType.ERROR
                message.parse_error(out continuation_error, null)
                Idle.add(continuation)
            when Gst.MessageType.EOS
                Idle.add(continuation)
            default
                pass

