[indent=4]

const style: string = """
style "custom"
{
    GtkRange::slider-width = 36
    GtkComboBox::arrow-size = 24
    font_name = "Sans 18"
}

widget_class "*Scrollbar*" style "custom"
"""

init
    Gtk.init(ref args)
    Gtk.rc_parse_string(style)
    Gst.init(ref args)
    var window = new PlayerWindow()
    window.show()
    Gtk.main()

