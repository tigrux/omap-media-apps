[indent=4]

uses Gst


class MediaControl: GLib.Object
    _pipeline: Bin
    prepare_xwindow_q: static Quark = Quark.from_string("prepare-xwindow-id")
    xoverlay: XOverlay

    event prepare_xwindow_id(imagesink: XOverlay)
    event tag_found(name: string, tag_value: GLib.Value)

    event eos_message(src: Gst.Object)
    event error_message(src: Gst.Object, error: Error, debug: string)
    event element_message(src: Gst.Object, structure: Structure)
    event segment_start_message(src: Gst.Object, format: Format, pos: int64)
    event segment_done_message(src: Gst.Object, format: Format, pos: int64)
    event tag_message(src: Gst.Object, tag_list: TagList)
    event state_changed_message(src: Gst.Object, \
            old: State, current: State, pending: State)

    final
        if _pipeline != null
            remove_signals()

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

    prop pipeline: Bin
        set
            if _pipeline != null
                remove_signals()
            _pipeline = value
            add_signals()
        get
            return _pipeline

    def on_bus_message(message: Message)
        case message.type
            when MessageType.ELEMENT
                st: Structure
                if (st = message.structure) != null
                    element_message(message.src, st)
            when MessageType.EOS
                eos_message(message.src)
            when MessageType.ERROR
                e: Error
                d: string
                message.parse_error(out e, out d)
                error_message(message.src, e, d)
            when MessageType.STATE_CHANGED
                old, current, pending: State
                message.parse_state_changed(out old, out current, out pending)
                state_changed_message(message.src, old, current, pending)
            when MessageType.SEGMENT_START
                format: Format
                position: int64
                message.parse_segment_start(out format, out position)
                segment_start_message(message.src, format, position)
            when MessageType.SEGMENT_DONE
                format: Format
                position: int64
                message.parse_segment_done(out format, out position)
                segment_done_message(message.src, format, position)
            when MessageType.TAG
                tag_list: TagList
                message.parse_tag(out tag_list)
                tag_list.for_each(tag_foreach_func)
                tag_message(message.src, tag_list)
            default
                pass

    def tag_foreach_func(tag_list: TagList, tag_name: string)
        tag_value: GLib.Value
        TagList.copy_value(out tag_value, tag_list, tag_name)
        tag_found(tag_name, tag_value)

    def on_bus_sync_message(message: Message)
        structure: Structure
        if (structure = message.structure) == null
            return
        if structure.name == prepare_xwindow_q
            xoverlay = message.src as XOverlay
            prepare_xwindow_id(xoverlay)

    prop state: State
        get
            state: State
            pipeline.get_state(out state, null, (ClockTime)(MSECOND*50))
            return state
        set
            pipeline.set_state(value)

    prop position: int64
        get
            var format = Format.TIME
            position: int64
            pipeline.query_position(ref format, out position)
            return position
        set
            var seek_event = new Event.seek( \
                1.0, Format.TIME, \
                SeekFlags.FLUSH | SeekFlags.ACCURATE, \
                Gst.SeekType.SET, value, \
                Gst.SeekType.NONE, 0)
            pipeline.send_event(seek_event)

    prop duration: int64
        get
            var format = Format.TIME
            duration: int64
            pipeline.query_duration(ref format, out duration)
            return duration

