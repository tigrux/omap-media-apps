[indent=4]

uses Gst


class MediaControl: GLib.Object
    bus: Bus
    _pipeline: Bin

    event eos_message(src: Gst.Object)
    event error_message(src: Gst.Object, error: Error, debug: string)
    event element_message(src: Gst.Object, structure: Structure)
    event segment_start_message(src: Gst.Object, format: Format, pos: int64)
    event segment_done_message(src: Gst.Object, format: Format, pos: int64)
    event tag_message(src: Gst.Object, tag_list: TagList)
    event state_changed_message(src: Gst.Object, \
            old: Gst.State, current: Gst.State, pending: Gst.State)

    prop pipeline: Bin
        set
            if bus != null
                bus.message.disconnect(on_bus_message)
            _pipeline = value
            bus = pipeline.get_bus()
            bus.add_signal_watch()
            bus.message += on_bus_message
        get
            return _pipeline

    def get_bus(): Bus
        return bus

    def on_bus_message(message: Message)
        case message.type
            when Gst.MessageType.ELEMENT
                st: Structure
                if (st = message.structure) != null
                    element_message(message.src, st)
            when Gst.MessageType.EOS
                eos_message(message.src)
            when Gst.MessageType.ERROR
                e: Error
                d: string
                message.parse_error(out e, out d)
                error_message(message.src, e, d)
            when Gst.MessageType.STATE_CHANGED
                old, current, pending: Gst.State
                message.parse_state_changed(out old, out current, out pending)
                state_changed_message(message.src, old, current, pending)
            when Gst.MessageType.SEGMENT_START
                format: Format
                position: int64
                message.parse_segment_start(out format, out position)
                segment_start_message(message.src, format, position)
            when Gst.MessageType.SEGMENT_DONE
                format: Format
                position: int64
                message.parse_segment_done(out format, out position)
                segment_done_message(message.src, format, position)
            when Gst.MessageType.TAG
                tag_list: TagList
                message.parse_tag(out tag_list)
                tag_message(message.src, tag_list)
            default
                pass

    def seek(location: int64)
        var seek_event = new Event.seek( \
            1.0, Format.TIME, \
            SeekFlags.FLUSH | SeekFlags.ACCURATE, \
            Gst.SeekType.SET, location, \
            Gst.SeekType.NONE, 0)
        pipeline.send_event(seek_event)

    def get_state(): Gst.State
        state: State
        pipeline.get_state(out state, null, (ClockTime)(MSECOND*50))
        return state

    def set_state(state: Gst.State): StateChangeReturn
        return pipeline.set_state(state)

    def get_position(): int64
        var format = Format.TIME
        position: int64
        pipeline.query_position(ref format, out position)
        return position

    def get_duration(): int64
        var format = Format.TIME
        duration: int64
        pipeline.query_duration(ref format, out duration)
        return duration

