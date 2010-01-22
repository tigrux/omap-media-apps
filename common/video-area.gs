[indent=4]

uses Gtk
uses Gst


class VideoArea: DrawingArea
    xid: uint32
    _imagesink: dynamic Gst.XOverlay

    event activated()

    init
        double_buffered = false
        add_events(Gdk.EventMask.BUTTON_PRESS_MASK)
        add_events(Gdk.EventMask.BUTTON_RELEASE_MASK)
        realize += def()
            xid = Gdk.x11_drawable_get_xid(window)

    prop sink: Gst.XOverlay
        set
            _imagesink = value
            _imagesink.force_aspect_ratio = true
            _imagesink.set_xwindow_id(xid)
        get
            return _imagesink

    def override button_press_event(event: Gdk.EventButton): bool
        if event.type == Gdk.EventType.2BUTTON_PRESS
            activated()
        return true

    def override expose_event(e: Gdk.EventExpose): bool
        if _imagesink != null
            _imagesink.expose()
            return false
        Gdk.draw_rectangle( \
            e.window, get_style().black_gc, true, \
            e.area.x, e.area.y, e.area.width, e.area.height)
        return true

