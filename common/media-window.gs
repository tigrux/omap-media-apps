[indent=4]

uses Gtk

const DEFAULT_STYLE: string = """
style "custom"
{
    GtkRange::slider-width = 24
    GtkComboBox::arrow-size = 18
    GtkComboBox::appears-as-list = 1
    font_name = "Sans 12"
}

widget_class "*" style "custom"
"""


class MediaWindow: Window
    notebook: Notebook
    toolbar: Toolbar
    main_box: VBox
    rc_parsed: static bool = rc_parse()

    enum Tab
        LIST
        VIDEO

    def static rc_parse(): bool
        rc_parse_string(DEFAULT_STYLE)
        return true

    init
        settings: Gtk.Settings = get_settings()
        settings.set("gtk-touchscreen-mode", true)

        set_default_size(800, 480)
        destroy += on_quit

        main_box = new VBox(false, 0)
        add(main_box)

        toolbar = new Toolbar()
        toolbar.set_icon_size(IconSize.DND)
        main_box.pack_start(toolbar, false, false, 0)

        notebook = new Notebook()
        notebook.set_show_tabs(false)
        main_box.pack_start(notebook, true, true, 0)
        main_box.show_all()

    def toolbar_add_quit_button()
        toolbar_add_expander()

        var quit_button = new ToolButton.from_stock(STOCK_QUIT)
        toolbar.add(quit_button)
        quit_button.clicked += on_quit

    def toolbar_add_expander()
        var expander_item = new SeparatorToolItem()
        expander_item.set_expand(true)
        expander_item.set_draw(false)
        toolbar.add(expander_item)

    def set_fullscreen(value: bool)
        for child in main_box.get_children()
            if child != notebook
                child.set_visible(not value)
        if value
            fullscreen()
        else
            unfullscreen()

    def on_quit()
        Idle.add(quit)

    def quit(): bool
        Gtk.main_quit()
        return false