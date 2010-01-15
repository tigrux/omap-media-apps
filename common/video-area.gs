[indent=4]

uses Gtk
uses Gst

class VideoArea: DrawingArea
    xid: uint32
    imagesink: Gst.XOverlay
    bus: Bus

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
        imagesink.set("force-aspect-ratio", true, null)
        imagesink.set_xwindow_id(xid)

    def override button_press_event(event: Gdk.EventButton): bool
        if event.type == Gdk.EventType.2BUTTON_PRESS
            activated()
        return true

    def override expose_event(event: Gdk.EventExpose): bool
        if imagesink != null
            imagesink.expose()
            return false
        return true

    def set_bus(bus: Bus)
        this.bus = bus
        bus.enable_sync_message_emission()
        bus.sync_message.connect(on_bus_sync_message)

    def on_bus_sync_message(message: Gst.Message)
        if message.structure == null
            return
        var message_name = message.structure.get_name()
        if message_name == "prepare-xwindow-id"
            var imagesink = message.src as Gst.XOverlay
            set_sink(imagesink)
            prepared()

