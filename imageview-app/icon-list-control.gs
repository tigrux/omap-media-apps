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

    prop iconlist_store: ListStore
    continuation: SourceFunc
    continuation_error: Error

    construct(model: ListStore) raises Error
        pipeline = parse_launch(PIXBUF_PIPELINE_DESC) as Pipeline
        if (filesrc = pipeline.get_by_name("filesrc")) == null
            raise new CoreError.FAILED( \
                        "No element named filesrc in the pixbuf pipeline")
        if (imagesink = pipeline.get_by_name("imagesink")) == null
            raise new CoreError.FAILED( \
                        "No element named imagesink in the pixbuf pipeline")
        iconlist_store = model
        var bus = pipeline.bus
        bus.add_signal_watch()
        bus.message += on_bus_message

    final
        if pipeline != null
            pipeline.set_state(State.NULL)

    def async add_file(filename: string, displayname: string) raises Error
        continuation = add_file.callback
        filesrc.location = filename
        pipeline.set_state(State.PLAYING)
        yield

        if continuation_error == null
            pixbuf: Gdk.Pixbuf = imagesink.last_pixbuf
            if pixbuf != null
                iconlist_store.insert_with_values(null, -1, \
                    ImageListCol.TEXT, displayname, \
                    ImageListCol.FILE, filename, \
                    ImageListCol.PIXBUF, pixbuf)
        else
            error: Error = (owned)continuation_error
            raise error
        pipeline.set_state(State.READY)

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
                        var display = info.get_display_name()
                        try
                            yield add_file(file, display)
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

