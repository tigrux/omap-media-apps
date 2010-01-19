[indent=4]


init
    Gst.init(ref args)
    Gtk.init(ref args)
    try
        var window = new ImageViewWindow()
        window.show()
        Gtk.main()
    except e: Error
        error_dialog(e)

