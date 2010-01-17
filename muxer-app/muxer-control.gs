[indent=4]

uses Gst


class MuxerControl: GLib.Object implements Control
    preview_desc: string
    record_desc: string
    recording: bool
    previewing: bool
    buffer_probe_enabled: bool

    event eos()
    event error_message(e: Error, debug: string)

    def get_bus(): Bus
        return preview_bin.bus

    def enable_buffer_probe(enabled: bool)
        buffer_probe_enabled = enabled

    overlay: Element
    tee: Element
    audiosrc: Element
    preview_bin: Gst.Bin
    record_bin: Gst.Bin
    queue: Element

    adjust_ts_video: ClockTime
    adjust_ts_audio: ClockTime
    video_probe_id: uint
    audio_probe_id: uint

    error_dialog: ErrorDialog

    construct(preview: string, record: string)
        preview_desc = preview
        record_desc = record

    def load() raises Error
        load_preview_pipeline()

    def is_previewing(): bool
        return previewing

    def is_recording(): bool
        return recording

    def start_preview()
        if preview_bin.set_state(State.PLAYING) != StateChangeReturn.FAILURE
            previewing = true

    def stop_preview()
        preview_bin.set_state(State.NULL)
        previewing = false

    def start_record() raises Error
        if buffer_probe_enabled
            preview_bin.set_state(State.PAUSED)
        else
            preview_bin.set_state(State.NULL)
        load_record_pipeline()
        preview_bin.add(record_bin)
        tee.link(queue)
        var tee_src1_pad = tee.get_static_pad("src1")
        if buffer_probe_enabled
            video_probe_id = tee_src1_pad.add_buffer_probe(video_buffer_probe)
        if buffer_probe_enabled and audiosrc != null
            var audio_src_pad = audiosrc.get_static_pad("src")
            audio_probe_id = audio_src_pad.add_buffer_probe(audio_buffer_probe)
        if overlay != null
            overlay.set("silent", false)
        if preview_bin.set_state(State.PLAYING) != StateChangeReturn.FAILURE
            recording = true

    def stop_record()
        if not recording
            return
        tee.set_state(State.PAUSED)
        if overlay != null
            overlay.set("silent", true)
        self.tee.unlink(self.queue)
        preview_bin.remove(record_bin)
        record_bin.set_bus(preview_bin.get_bus())
        queue.send_event(new Event.eos())
        if audiosrc != null
            audiosrc.send_event(new Event.eos())
        tee.set_state(State.PLAYING)

    def load_preview_pipeline() raises Error
        preview_bin = parse_launch(preview_desc) as Gst.Bin
        var bus = preview_bin.get_bus()
        bus.add_signal_watch()
        bus.message += on_bus_message
        preview_bin.set_name("preview_bin")
        overlay = preview_bin.get_by_name("overlay")
        if (tee = preview_bin.get_by_name("tee")) == null
            raise new CoreError.FAILED( \
                        "No element named tee in the preview pipeline")

    def load_record_pipeline() raises Error
        record_bin = parse_launch(record_desc) as Gst.Bin
        record_bin.set_name("record_bin")
        if (queue = record_bin.get_by_name("queue")) == null
            raise new CoreError.FAILED( \
                        "No element named queue in the record pipeline")
        audiosrc = record_bin.get_by_name("audiosrc")

    def on_bus_message(message: Message)
        case message.type
            when Gst.MessageType.EOS
                record_bin.set_state(State.NULL)
                recording = false
                eos()
            when Gst.MessageType.ERROR
                e: Error
                debug: string
                message.parse_error(out e, out debug)
                error_message(e, debug)
                shutdown()
                eos()
            default
                pass

    def shutdown()
        stop_record()
        stop_preview()

    def video_buffer_probe(pad: Pad, buffer: Buffer): bool
        if adjust_ts_video == 0
            adjust_ts_video = buffer.timestamp
            var parent = pad.get_parent() as Element
            var sinkpad = parent.get_static_pad("sink")
            var event = new Event.new_segment(\
                false, 1.0, Format.TIME, 0, -1, 0)
            sinkpad.send_event(event)
            buffer.flags |= BufferFlag.DISCONT
        buffer.timestamp -= adjust_ts_video
        return true

    def audio_buffer_probe(pad: Pad, buffer: Buffer): bool
        if adjust_ts_audio == 0
            adjust_ts_audio = buffer.timestamp
            var peerpad = pad.get_peer()
            var event = new Event.new_segment(\
                false, 1.0, Format.TIME, 0, -1, 0)
            peerpad.send_event(event)
            buffer.flags |= BufferFlag.DISCONT
        buffer.timestamp -= adjust_ts_audio
        return true

