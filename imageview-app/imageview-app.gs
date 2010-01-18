[indent=4]


init
    Gst.init(ref args)
    Gtk.init(ref args)
    Gtk.rc_parse_string(DEFAULT_STYLE)
    try
        var window = new ImageViewWindow()
        window.show()
        Gtk.main()
    except e: Error
        error_dialog(e)

