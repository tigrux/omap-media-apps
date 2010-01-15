[indent=4]


init
    Gtk.init(ref args)
    Gtk.rc_parse_string(DEFAULT_STYLE)
    Gst.init(ref args)
    var window = new PlayerWindow()
    window.show()
    Gtk.main()

