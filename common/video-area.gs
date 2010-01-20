[indent=4]

uses Gtk
uses Gst


class VideoArea: DrawingArea
    xid: uint32
    bus: Bus
    imagesink: dynamic Gst.XOverlay
    prepare_xwindow_q: static Quark = Quark.from_string("prepare-xwindow-id")

    event prepared()
    event activated()

    init
        double_buffered = false
        add_events(Gdk.EventMask.BUTTON_PRESS_MASK)
        add_events(Gdk.EventMask.BUTTON_RELEASE_MASK)
        realize += def()
            xid = Gdk.x11_drawable_get_xid(window)

    final
        if bus != null
           bus.sync_message.disconnect(on_bus_sync_message)

    def set_sink(sink: Gst.XOverlay)
        imagesink = sink
        imagesink.force_aspect_ratio = true
        imagesink.set_xwindow_id(xid)

    def override button_press_event(event: Gdk.EventButton): bool
        if event.type == Gdk.EventType.2BUTTON_PRESS
            activated()
        return true

    def override expose_event(e: Gdk.EventExpose): bool
        if imagesink != null
            imagesink.expose()
            return false
        Gdk.draw_rectangle( \
            e.window, get_style().black_gc, true, \
            e.area.x, e.area.y, e.area.width, e.area.height)
        return true

    def set_control(control: MediaControl)
        bus = control.pipeline.bus
        bus.enable_sync_message_emission()
        bus.sync_message += on_bus_sync_message

    def on_bus_sync_message(message: Gst.Message)
        structure: Structure
        if (structure = message.structure) == null
            return
        if structure.name == prepare_xwindow_q
            var imagesink = message.src as Gst.XOverlay
            set_sink(imagesink)
            prepared()

