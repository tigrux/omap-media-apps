[indent=4]

uses Gtk


class MediaWindow: Window
    notebook: Notebook
    toolbar: Toolbar
    main_box: VBox
    style_applied: static bool = apply_style()
    is_fullscreen: bool

    enum Tab
        LIST
        VIDEO

    def static apply_style(): bool
        for dir in Environment.get_system_data_dirs()
            var rc_file = Path.build_filename(dir, "omap4-apps", "style.rc")
            if FileUtils.test(rc_file, FileTest.IS_REGULAR)
                rc_parse(rc_file)
                    return true
        return false

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

    def lookup_and_set_icon_name(name: string)
        var theme = IconTheme.get_default()
        var icon_info = theme.lookup_icon(name, 48, 0)
        if icon_info != null
            try
                set_icon_from_file(icon_info.get_filename())
            except
                pass

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

    def toggle_fullscreen()
        is_fullscreen = not is_fullscreen
        set_fullscreen(is_fullscreen)

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
