[indent=4]

uses Gtk


const style: string = """
style "custom"
{
    GtkComboBox::appears-as-list = 1
}

widget_class "*ComboBox*" style "custom"
"""


init
    Gtk.init(ref args)
    Gst.init(ref args)
    Gtk.rc_parse_string(style)
    var window = new ImageViewWindow()
    window.show()
    Gtk.main()
