[indent=4]


class Omap.MediaControl: GLib.Object
    _pipeline: Gst.Bin
    prepare_xwindow_q: static Quark = Quark.from_string("prepare-xwindow-id")
    xoverlay: Gst.XOverlay

    event prepare_xwindow_id(imagesink: Gst.XOverlay)
    event tag_found(name: string, tag_value: GLib.Value)

    event eos_message(src: Gst.Object)
    event error_message(src: Gst.Object, error: Error, debug: string)
    event element_message(src: Gst.Object, structure: Gst.Structure)
    event segment_start_message(src: Gst.Object, format: Gst.Format, pos: int64)
    event segment_done_message(src: Gst.Object, format: Gst.Format, pos: int64)
    event tag_message(src: Gst.Object, tag_list: Gst.TagList)
    event state_changed_message(src: Gst.Object,
            old: Gst.State, current: Gst.State, pending: Gst.State)

    final
        pipeline = null

    def remove_signals()
        var bus = _pipeline.bus
        bus.message.disconnect(on_bus_sync_message)
        bus.message.disconnect(on_bus_message)
        bus.disable_sync_message_emission()
        bus.remove_signal_watch()

    def add_signals()
        var bus = _pipeline.bus
        bus.add_signal_watch()
        bus.enable_sync_message_emission()
        bus.message += on_bus_message
        bus.sync_message += on_bus_sync_message

    prop pipeline: Gst.Bin
        set
            if _pipeline != null
                state = Gst.State.NULL
                remove_signals()
            _pipeline = value
            if value != null
                add_signals()
        get
            return _pipeline

    prop state: Gst.State
        get
            state: Gst.State
            pipeline.get_state(out state, null, (Gst.ClockTime)(Gst.MSECOND*50))
            return state
        set
            pipeline.set_state(value)

    prop position: int64
        get
            var format = Gst.Format.TIME
            position: int64
            pipeline.query_position(ref format, out position)
            return position
        set
            var seek_event = new Gst.Event.seek(
                1.0, Gst.Format.TIME,
                Gst.SeekFlags.FLUSH | Gst.SeekFlags.ACCURATE,
                Gst.SeekType.SET, value,
                Gst.SeekType.NONE, 0)
            pipeline.send_event(seek_event)

    prop duration: int64
        get
            var format = Gst.Format.TIME
            duration: int64
            pipeline.query_duration(ref format, out duration)
            return duration

    def on_bus_message(message: Gst.Message)
        case message.type()
            when Gst.MessageType.ELEMENT
                st: Gst.Structure
                if (st = message.get_structure()) != null
                    element_message(message.src(), st)
            when Gst.MessageType.EOS
                eos_message(message.src())
            when Gst.MessageType.ERROR
                e: Error
                d: string
                message.parse_error(out e, out d)
                error_message(message.src(), e, d)
            when Gst.MessageType.STATE_CHANGED
                old, current, pending: Gst.State
                message.parse_state_changed(out old, out current, out pending)
                state_changed_message(message.src(), old, current, pending)
            when Gst.MessageType.SEGMENT_START
                format: Gst.Format
                position: int64
                message.parse_segment_start(out format, out position)
                segment_start_message(message.src(), format, position)
            when Gst.MessageType.SEGMENT_DONE
                format: Gst.Format
                position: int64
                message.parse_segment_done(out format, out position)
                segment_done_message(message.src(), format, position)
            when Gst.MessageType.TAG
                tag_list: Gst.TagList
                message.parse_tag(out tag_list)
                tag_list.foreach(tag_foreach_func)
                tag_message(message.src(), tag_list)
            default
                pass

    def tag_foreach_func(tag_list: Gst.TagList, tag_name: string)
        tag_value: GLib.Value
        Gst.TagList.copy_value(out tag_value, tag_list, tag_name)
        tag_found(tag_name, tag_value)

    def on_bus_sync_message(message: Gst.Message)
        structure: Gst.Structure
        if (structure = message.get_structure()) == null
            return
        if structure.name == prepare_xwindow_q
            xoverlay = message.src() as Gst.XOverlay
            prepare_xwindow_id(xoverlay)

