[indent=4]

uses Gst


class MediaControl: GLib.Object
    bus: Bus
    pipeline: Bin

    event eos_message()
    event error_message(error: Error, debug: string)
    event structure_message(src: Gst.Object, name: string)

    def set_pipeline(bin: Bin)
        if bus != null
            bus.message.disconnect(on_bus_message)
        pipeline = bin
        bus = pipeline.get_bus()
        bus.add_signal_watch()
        bus.message += on_bus_message

    def get_bus(): Bus
        return bus

    def on_bus_message(message: Message)
        case message.type
            when Gst.MessageType.ELEMENT
                st: Structure
                if (st = message.structure) != null
                    structure_message(message.src, st.get_name())
            when Gst.MessageType.EOS
                eos_message()
            when Gst.MessageType.ERROR
                e: Error
                d: string
                message.parse_error(out e, out d)
                error_message(e, d)
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

