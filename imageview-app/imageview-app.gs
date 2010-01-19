[indent=4]


init
    Gst.init(ref args)
    Gtk.init(ref args)
    var window = new ImageViewWindow()
    window.show()
    Gtk.main()

