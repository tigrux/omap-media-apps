[indent=4]

uses Gst


class MuxerControl: MediaControl
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

    overlay: dynamic Element
    tee: Element
    videosrc: Element
    audiosrc: Element
    preview_bin: Gst.Bin
    record_bin: Gst.Bin
    queue: Element

    adjust_ts_video: ClockTime
    adjust_ts_audio: ClockTime

    init
        error_message += on_error
        eos_message += on_eos
        state_changed_message += on_state_changed

    construct(preview: string, record: string)
        preview_desc = preview
        record_desc = record

    final
        shutdown()

    def load() raises Error
        load_preview_bin()

    def start_preview()
        preview_bin.set_state(State.PLAYING)

    def stop_preview()
        preview_bin.set_state(State.NULL)
        _previewing = false

    def start_record() raises Error
        preview_bin.set_state(State.NULL)
        load_record_bin()
        preview_bin.add(record_bin)
        tee.link(queue)
        if overlay != null
            overlay.silent = false
        preview_bin.set_state(State.PLAYING)

    def stop_record()
        if not _recording
            return
        videosrc.send_event(new Event.eos())
        if audiosrc != null
            audiosrc.send_event(new Event.eos())
        if overlay != null
            overlay.silent = true

    def load_preview_bin() raises Error
        preview_bin = parse_launch(preview_desc) as Gst.Bin
        print "bus 1 = %p", preview_bin.bus
        preview_bin.set_name("preview_bin")
        pipeline = preview_bin
        overlay = preview_bin.get_by_name("overlay")
        videosrc = preview_bin.get_by_name("videosrc")
        if (tee = preview_bin.get_by_name("tee")) == null
            raise new CoreError.FAILED( \
                        "No element named tee in the preview pipeline")

    def load_record_bin() raises Error
        record_bin = parse_launch(record_desc) as Gst.Bin
        print "bus 2 = %p", record_bin.bus
        record_bin.set_name("record_bin")
        if (queue = record_bin.get_by_name("queue")) == null
            raise new CoreError.FAILED( \
                        "No element named queue in the record pipeline")
        audiosrc = record_bin.get_by_name("audiosrc")

    def on_state_changed(src: Gst.Object, \
                       old: Gst.State, current: Gst.State, pending: Gst.State)
        if src == preview_bin
            print "%s: %s -> %s", src.name, old.to_string(), current.to_string()
            if old == State.PAUSED and current == State.PLAYING
                _previewing = true
                preview_started()
            if old == State.READY and current == State.NULL
                _previewing = false
                preview_stopped()
        else
        if src == record_bin
            print "%s: %s -> %s", src.name, old.to_string(), current.to_string()
            if old == State.PAUSED and current == State.PLAYING
                _recording = true
                record_started()

    def on_eos(src: Gst.Object)
        print "%s: eos, %s", src.name, state.to_string()
        _recording = false
        preview_bin.set_state(State.NULL)
        self.tee.unlink(self.queue)
        preview_bin.remove(record_bin)
        preview_bin.set_state(State.PLAYING)
        record_stopped()

    def on_error(src: Gst.Object, e: Error, debug: string)
        print e.message
        print debug
        shutdown()

    def shutdown()
        stop_record()
        stop_preview()

