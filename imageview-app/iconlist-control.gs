[indent=4]

uses Gst
uses Gtk


const PIXBUF_PIPELINE_DESC: string = """
filesrc name=filesrc ! jpegdec ! ffmpegcolorspace ! videoscale !
video/x-raw-rgb,width=128,height=96 ! gdkpixbufsink name=imagesink
"""

const IMAGE_FILE_ATTRIBUTES: string = "standard::name,standard::display-name,standard::content-type"


class IconListControl: GLib.Object
    enum Col
        TEXT
        FILE
        PIXBUF
        VALID

    pipeline: Pipeline
    filesrc: dynamic Element
    imagesink: dynamic Element
    missing_pixbuf: Gdk.Pixbuf
    loading_pixbuf: static Gdk.Pixbuf
    last_pixbuf: static Gdk.Pixbuf
    pixbuf_q: static Quark = Quark.from_string("pixbuf")
    pixbufs_loaded: static bool

    prop iconlist_store: ListStore
    continuation: SourceFunc
    continuation_error: Error

    event done()

    construct(model: ListStore) raises Error
        iconlist_store = model
        if not pixbufs_loaded
            setup_icons()
            pixbufs_loaded = true
        setup_elements()
            
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
        var bus = pipeline.get_bus()
        bus.add_signal_watch()
        bus.message += on_bus_message

    def async add_folder(dirname: string, cancellable: Cancellable)
        var dir = File.new_for_path (dirname)
        try
            var file_etor = yield dir.enumerate_children_async( \
                                    IMAGE_FILE_ATTRIBUTES, \
                                    FileQueryInfoFlags.NONE, \
                                    Priority.DEFAULT, cancellable)
            while not cancellable.is_cancelled()
                var next_files = yield file_etor.next_files_async( \
                                    5, Priority.DEFAULT, cancellable)
                if next_files == null
                    break
                add_next_files(dirname, next_files)
            if not cancellable.is_cancelled()
                yield retrieve_thumbnails(cancellable)
        except e1: Error
            print e1.message
        finally
            done()

    def add_next_files(dirname: string, files: GLib.List of FileInfo)
        for info in files
            if info.get_content_type() == "image/jpeg"
                var file = Path.build_filename(dirname, info.get_name())
                var text = info.get_display_name()
                iconlist_store.insert_with_values(null, -1, \
                    Col.TEXT, text, \
                    Col.FILE, file, \
                    Col.PIXBUF, loading_pixbuf, \
                    -1)

    def async retrieve_thumbnails(cancellable: Cancellable)
        iter: TreeIter
        if iconlist_store.get_iter_first(out iter)
            continuation = retrieve_thumbnails.callback
            pipeline.set_state(State.READY)
            do
                file: string
                display: string
                iconlist_store.get(iter, \
                    Col.TEXT, out display, \
                    Col.FILE, out file, \
                    -1)
                continuation_error = null
                filesrc.location = file
                pipeline.set_state(State.PLAYING)
                yield
                pipeline.set_state(State.READY)
                pixbuf: Gdk.Pixbuf
                valid: bool
                if (valid = continuation_error == null and last_pixbuf != null)
                    pixbuf = (owned)last_pixbuf
                else
                    pixbuf = missing_pixbuf
                iconlist_store.set(iter, \
                    Col.PIXBUF, pixbuf, \
                    Col.VALID, valid, \
                    -1)
            while \
                iconlist_store.iter_next(ref iter) and \
                not cancellable.is_cancelled()
            pipeline.set_state(State.NULL)

    def on_bus_message(message: Gst.Message)
        case message.type
            when Gst.MessageType.ERROR
                message.parse_error(out continuation_error, null)
                Idle.add(continuation)
            when Gst.MessageType.ELEMENT
                if message.src == imagesink
                    structure: Structure
                    if (structure = message.structure) != null
                        if structure.name == pixbuf_q
                            last_pixbuf = imagesink.last_pixbuf
            when Gst.MessageType.EOS
                Idle.add(continuation)
            default
                pass

    def static get_text_column(): Col
        return Col.TEXT

    def static get_pixbuf_column(): Col
        return Col.PIXBUF

    def iter_get_valid(iter: TreeIter): bool
        valid: bool
        iconlist_store.get(iter, Col.VALID, out valid, -1)
        return valid

    def iter_get_file(iter: TreeIter): string
        file: string
        iconlist_store.get(iter, Col.FILE, out file, -1)
        return file

