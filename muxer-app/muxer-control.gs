[indent=4]


class Omap.MuxerControl: MediaControl
    preview_desc: string
    record_desc: string
    _recording: bool
    _previewing: bool

    event preview_started()
    event preview_stopped()
    event record_started()
    event record_stopped()

    prop previewing: bool
        get
            return _previewing

    prop recording: bool
        get
            return _recording

    overlay: dynamic Gst.Element
    tee: Gst.Element
    videosrc: Gst.Element
    audiosrc: Gst.Element
    filesrc: Gst.Element
    preview_bin: Gst.Bin
    record_bin: Gst.Bin
    queue: Gst.Element

    adjust_ts_video: Gst.ClockTime
    adjust_ts_audio: Gst.ClockTime

    init
        eos_message += on_eos
        state_changed_message += on_state_changed

    construct(preview: string, record: string)
        preview_desc = preview
        record_desc = record

    final
        stop()

    def load() raises Error
        load_preview_bin()

    def start_preview()
        state = Gst.State.PLAYING

    def stop_preview()
        if pipeline != null
            state = Gst.State.NULL
            _previewing = false
            preview_stopped()

    def start_record() raises Error
        state = Gst.State.NULL
        load_record_bin()
        preview_bin.add(record_bin)
        tee.link(queue)
        if overlay != null
            overlay.silent = false
        state = Gst.State.PLAYING

    def stop_record()
        if not _recording
            return
        videosrc.send_event(new Gst.Event.eos())
        if audiosrc != null
            audiosrc.send_event(new Gst.Event.eos())

    def stop()
        stop_preview()

    def load_preview_bin() raises Error
        preview_bin = Gst.parse_launch(preview_desc) as Gst.Pipeline
        preview_bin.name = "preview_bin"
        pipeline = preview_bin
        overlay = preview_bin.get_by_name("overlay")
        videosrc = preview_bin.get_by_name("videosrc")
        if (tee = preview_bin.get_by_name("tee")) == null
            raise new Gst.CoreError.FAILED(
                        "No element named tee in the preview pipeline")

    def load_record_bin() raises Error
        record_bin = Gst.parse_launch(record_desc) as Gst.Pipeline
        record_bin.name = "record_bin"
        if (queue = record_bin.get_by_name("queue")) == null
            raise new Gst.CoreError.FAILED(
                        "No element named queue in the record pipeline")
        audiosrc = record_bin.get_by_name("audiosrc")
        filesrc = record_bin.get_by_name("filesrc")

    def on_state_changed(src: Gst.Object,
                       old: Gst.State, current: Gst.State, pending: Gst.State)
        if src == preview_bin
            if old == Gst.State.PAUSED and current == Gst.State.PLAYING
                _previewing = true
                preview_started()
        else
        if src == record_bin
            if old == Gst.State.PAUSED and current == Gst.State.PLAYING
                _recording = true
                record_started()

    def on_eos(src: Gst.Object)
        if overlay != null
            overlay.silent = true
        _recording = false
        record_stopped()
        stop_preview()
        tee.unlink(queue)
        preview_bin.remove(record_bin)
        prepare_xwindow_id(xoverlay)
        start_preview()

