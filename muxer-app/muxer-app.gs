[indent=4]

uses Gtk

const style: string = """
style "custom"
{
    GtkRange::slider-width = 36
    GtkComboBox::arrow-size = 24
    font_name = "Sans 18"
}

widget_class "*ComboBoxEntry*" style "custom"
widget_class "*Menu*" style "custom"
widget_class "*Scrollbar*" style "custom"
widget_class "*FileChooserButton*" style "custom"
"""

init
    Gtk.init(ref args)
    Gtk.rc_parse_string(style)
    Gst.init(ref args)
    var window = new MuxerWindow()
    window.show()
    Gtk.main()

