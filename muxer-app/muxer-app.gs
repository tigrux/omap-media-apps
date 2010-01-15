[indent=4]


init
    Gst.init(ref args)
    Gtk.init(ref args)
    Gtk.rc_parse_string(DEFAULT_STYLE)
    var window = new MuxerWindow()
    window.show()
    Gtk.main()

