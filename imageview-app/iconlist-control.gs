[indent=4]


const ICON_PIPELINE_DESC: string = \
"""filesrc name=filesrc ! jpegdec name=imagedec ! ffmpegcolorspace ! videoscale !
video/x-raw-rgb,width=128,height=96 ! gdkpixbufsink name=imagesink"""

const IMAGE_FILE_ATTRIBUTES: string = \
"standard::name,standard::display-name,standard::content-type"


class Omap.IconListControl: Omap.MediaControl
    enum Col
        TEXT
        FILE
        PIXBUF
        VALID
        FILLED
        WIDTH
        HEIGHT

    filesrc: dynamic Gst.Element
    imagesink: dynamic Gst.Element
    imagedec: dynamic Gst.Element
    imagedec_src: Gst.Pad

    missing_pixbuf: Gdk.Pixbuf
    loading_pixbuf: static Gdk.Pixbuf
    last_pixbuf: static Gdk.Pixbuf
    pixbuf_q: static Quark = Quark.from_string("pixbuf")
    pixbufs_loaded: static bool

    prop iconlist_store: Gtk.ListStore
    continuation: SourceFunc
    continuation_error: Error

    event files_added()
    event icons_filled()

    init
        eos_message.connect(on_eos)
        error_message.connect(on_error)
        element_message.connect(on_element)

    construct(model: Gtk.ListStore) raises Error
        iconlist_store = model
        if not pixbufs_loaded
            setup_icons()
            pixbufs_loaded = true
        setup_elements()

    def setup_icons() raises Error
        var icon_theme = Gtk.IconTheme.get_default()
        icon_info: Gtk.IconInfo

        icon_info = icon_theme.lookup_icon(
            Gtk.STOCK_MISSING_IMAGE, 96, Gtk.IconLookupFlags.FORCE_SIZE)
        if icon_info != null
            missing_pixbuf = icon_info.load_icon()

        icon_info = icon_theme.lookup_icon(
            "image-loading", 96, Gtk.IconLookupFlags.FORCE_SIZE)
        if icon_info != null
            loading_pixbuf = icon_info.load_icon()

    def setup_elements() raises Error
        setup_pipeline()

    def setup_pipeline() raises Error
        var icon_pipeline = Gst.parse_launch(ICON_PIPELINE_DESC) as Gst.Pipeline
        icon_pipeline.name = "icon_pipeline"
        if (filesrc = icon_pipeline.get_by_name("filesrc")) == null
            raise new Gst.CoreError.FAILED(
                        "No element named filesrc in the icon_pipeline")
        if (imagesink = icon_pipeline.get_by_name("imagesink")) == null
            raise new Gst.CoreError.FAILED(
                        "No element named imagesink in the icon_pipeline")
        if (imagedec = icon_pipeline.get_by_name("imagedec")) == null
            raise new Gst.CoreError.FAILED(
                        "No element named imagedec in the icon_pipeline")
        imagedec_src = imagedec.get_static_pad("src")

        pipeline = icon_pipeline

    def async add_folder(dirname: string, cancellable: Cancellable)
        var dir = File.new_for_path (dirname)
        try
            var file_etor = yield dir.enumerate_children_async(
                                    IMAGE_FILE_ATTRIBUTES,
                                    FileQueryInfoFlags.NONE,
                                    Priority.DEFAULT, cancellable)
            while not cancellable.is_cancelled()
                var next_files = yield file_etor.next_files_async(
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
                iconlist_store.insert_with_values(null, -1,
                    Col.TEXT, text,
                    Col.FILE, file,
                    Col.PIXBUF, loading_pixbuf,
                    -1)

    def async fill_icons(path: Gtk.TreePath, end: Gtk.TreePath,
                         cancellable: Cancellable)
        if path != null and end != null
            continuation = fill_icons.callback
            state = Gst.State.READY
            while not(path.compare(end) > 0 or cancellable.is_cancelled())
                iter: Gtk.TreeIter
                iconlist_store.get_iter(out iter, path)
                file: string
                filled: bool
                iconlist_store.get(iter,
                    Col.FILE, out file,
                    Col.FILLED, out filled,
                    -1)
                if not filled
                    continuation_error = null
                    last_pixbuf = null
                    filesrc.location = file
                    state = Gst.State.PLAYING
                    yield
                    width: int = 0
                    height: int = 0
                    pixbuf: Gdk.Pixbuf
                    valid: bool
                    valid = (continuation_error == null and last_pixbuf != null)
                    if valid
                        pixbuf = (owned)last_pixbuf
                        get_playing_image_size(out width, out height)
                    else
                        pixbuf = missing_pixbuf

                    iconlist_store.set(iter,
                        Col.PIXBUF, pixbuf,
                        Col.VALID, valid,
                        Col.FILLED, true,
                        Col.WIDTH, width,
                        Col.HEIGHT, height,
                        -1)
                state = Gst.State.READY
                path.next()
            state = Gst.State.NULL
        icons_filled()

    def get_playing_image_size(out width: int, out height: int)
        var st = imagedec_src.get_negotiated_caps().get_structure(0)
        st.get_int("width", out width)
        st.get_int("height", out height)

    def on_element(src: Gst.Object, structure: Gst.Structure)
        if src == imagesink and structure.get_name_id() == pixbuf_q
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

    def iter_is_valid(iter: Gtk.TreeIter): bool
        valid: bool
        iconlist_store.get(iter, Col.VALID, out valid, -1)
        return valid

    def iter_is_filled(iter: Gtk.TreeIter): bool
        filled: bool
        iconlist_store.get(iter, Col.FILLED, out filled, -1)
        return filled

    def iter_get_file(iter: Gtk.TreeIter): string
        file: string
        iconlist_store.get(iter, Col.FILE, out file, -1)
        return file

    def iter_get_size(iter: Gtk.TreeIter, out width: int, out height: int)
        iconlist_store.get(iter,
            Col.WIDTH, out width,
            Col.HEIGHT, out height,
            -1)

    def static model_new(): Gtk.ListStore
        var s = typeof(string)
        var p = typeof(Gdk.Pixbuf)
        var b = typeof(bool)
        var i = typeof(int)
        return new Gtk.ListStore(7, s, s, p, b, b, i, i)

