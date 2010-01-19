[indent=4]

uses Gtk


enum ApplicationTab
    LIST
    VIDEO


class ApplicationWindow: Window
    notebook: Notebook
    toolbar: Toolbar
    main_box: VBox
    rc_parsed: static bool = rc_parse()

    def static rc_parse(): bool
        rc_parse_string(DEFAULT_STYLE)
        return true

    init
        settings: Gtk.Settings = get_settings()
        settings.set("gtk-touchscreen-mode", true)

        set_default_size(DEFAULT_WIDTH, DEFAULT_HEIGHT)
        destroy += on_quit

        main_box = new VBox(false, 0)
        add(main_box)

        toolbar = new Toolbar()
        toolbar.set_icon_size(ICON_SIZE)
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

    def on_quit()
        Idle.add(quit)

    def quit(): bool
        Gtk.main_quit()
        return false
