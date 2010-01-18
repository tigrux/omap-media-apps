[indent=4]

uses Gst
uses Gtk


const ICON_PIPELINE_DESC: string = \
"""filesrc name=filesrc ! jpegdec ! ffmpegcolorspace ! videoscale !
video/x-raw-rgb,width=128,height=96 ! gdkpixbufsink name=imagesink"""


const IMAGE_FILE_ATTRIBUTES: string = \
"standard::name,standard::display-name,standard::content-type"


class IconListControl: MediaControl
    enum Col
        TEXT
        FILE
        PIXBUF
        VALID
        FILLED

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

    event files_added()
    event icons_filled()

    init
        eos_message += on_eos
        error_message += on_error
        element_message += on_element

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

    def setup_elements() raises Error
        setup_pipeline()

    def setup_pipeline() raises Error
        var icon_pipeline = parse_launch(ICON_PIPELINE_DESC) as Pipeline
        icon_pipeline.set_name("icon_pipeline")
        if (filesrc = icon_pipeline.get_by_name("filesrc")) == null
            raise new CoreError.FAILED( \
                        "No element named filesrc in the icon pipeline")
        if (imagesink = icon_pipeline.get_by_name("imagesink")) == null
            raise new CoreError.FAILED( \
                        "No element named imagesink in the icon pipeline")
        set_pipeline(icon_pipeline)

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
        except e1: Error
            error_dialog(e1)
        finally
            files_added()

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

    def async fill_icons(path: TreePath, end: TreePath, cancellable: Cancellable)
        if path != null and end != null
            continuation = fill_icons.callback
            pipeline.set_state(State.READY)
            while not(path.compare(end) > 0 or cancellable.is_cancelled())
                iter: TreeIter
                iconlist_store.get_iter(out iter, path)
                file: string
                filled: bool
                iconlist_store.get(iter, \
                    Col.FILE, out file, \
                    Col.FILLED, out filled, \
                    -1)
                if not filled
                    continuation_error = null
                    last_pixbuf = null
                    filesrc.location = file
                    pipeline.set_state(State.PLAYING)
                    yield
                    pipeline.set_state(State.READY)
                    pixbuf: Gdk.Pixbuf
                    valid: bool
                    valid = (continuation_error == null and last_pixbuf != null)
                    if valid
                        pixbuf = (owned)last_pixbuf
                    else
                        pixbuf = missing_pixbuf
                    iconlist_store.set(iter, \
                        Col.PIXBUF, pixbuf, \
                        Col.VALID, valid, \
                        Col.FILLED, true, \
                        -1)
                path.next()
            pipeline.set_state(State.NULL)
        icons_filled()

    def on_element(src: Gst.Object, structure: Structure)
        if src == imagesink and structure.name == pixbuf_q
            last_pixbuf = imagesink.last_pixbuf

    def on_error(src: Gst.Object, error: Error, debug: string)
        continuation_error = error
        Idle.add(continuation)

    def on_eos(src: Gst.Object)
        Idle.add(continuation)

    def static get_text_column(): Col
        return Col.TEXT

    def static get_pixbuf_column(): Col
        return Col.PIXBUF

    def iter_is_valid(iter: TreeIter): bool
        valid: bool
        iconlist_store.get(iter, Col.VALID, out valid, -1)
        return valid

    def iter_is_filled(iter: TreeIter): bool
        filled: bool
        iconlist_store.get(iter, Col.FILLED, out filled, -1)
        return filled

    def iter_get_file(iter: TreeIter): string
        file: string
        iconlist_store.get(iter, Col.FILE, out file, -1)
        return file

