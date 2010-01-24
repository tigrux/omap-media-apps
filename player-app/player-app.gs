[indent=4]


init
    Gst.init(ref args)
    Gtk.init(ref args)
    var window = new Omap.PlayerWindow()
    window.show()
    Gtk.main()

