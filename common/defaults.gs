[indent=4]

uses Gtk


const DEFAULT_WIDTH: int = 800

const DEFAULT_HEIGHT: int = 480

const ICON_SIZE: IconSize = IconSize.DND

const DEFAULT_STYLE: string = """
style "custom"
{
    GtkRange::slider-width = 12
    GtkComboBox::arrow-size = 12
    GtkComboBox::appears-as-list = 1
    font_name = "Sans 12"
}

widget_class "*" style "custom"
"""

