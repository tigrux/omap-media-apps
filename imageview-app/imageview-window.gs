[indent=4]

uses Gtk
uses Gst

class ImageViewWindow: Window
    init
        pass

init
    Gtk.init(ref args)
    Gst.init(ref args)
    var window = new ImageViewWindow()
    window.show()
    Gtk.main()
