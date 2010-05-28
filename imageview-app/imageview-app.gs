[indent=4]


init
    Gst.init(ref args)
    Gtk.init(ref args)
    try
        var window = new Omap.ImageViewWindow()
        window.setup_controls()
        window.on_chooser_folder_changed()
        window.show()
    except e: Error
        var dialog = Omap.error_dialog(e)
        dialog.destroy += Gtk.main_quit
    Gtk.main()

