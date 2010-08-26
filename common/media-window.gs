[indent=4]


class Omap.MediaWindow: Gtk.Window
    notebook: Gtk.Notebook
    toolbar: Gtk.Toolbar
    main_box: Gtk.VBox
    style_applied: static bool = apply_style()
    is_fullscreen: bool

    enum Tab
        LIST
        VIDEO

    def static apply_style(): bool
        for dir in Environment.get_system_data_dirs()
            var rc_file = Path.build_filename(dir, "omap4-apps", "style.rc")
            if FileUtils.test(rc_file, FileTest.IS_REGULAR)
                Gtk.rc_parse(rc_file)
                    return true
        return false

    init
        lookup_and_set_icon_name(Environment.get_prgname())
        settings: dynamic Gtk.Settings = get_settings()
        settings.gtk_touchscreen_mode = true

        set_default_size(800, 480)
        destroy.connect(on_destroy)

        main_box = new Gtk.VBox(false, 0)
        add(main_box)

        toolbar = new Gtk.Toolbar()
        toolbar.icon_size = Gtk.IconSize.DND
        main_box.pack_start(toolbar, false, false, 0)

        notebook = new Gtk.Notebook()
        notebook.show_tabs = false
        main_box.pack_start(notebook, true, true, 0)
        main_box.show_all()

    def lookup_and_set_icon_name(name: string)
        var theme = Gtk.IconTheme.get_default()
        var icon_info = theme.lookup_icon(name, 48, 0)
        if icon_info != null
            try
                set_icon_from_file(icon_info.get_filename())
            except
                pass

    def toolbar_add_quit_button()
        toolbar_add_expander()

        var quit_button = new Gtk.ToolButton.from_stock(Gtk.STOCK_QUIT)
        toolbar.add(quit_button)
        quit_button.clicked.connect(on_quit)

    def toolbar_add_expander()
        var expander_item = new Gtk.SeparatorToolItem()
        expander_item.set_expand(true)
        expander_item.set_draw(false)
        toolbar.add(expander_item)

    def toggle_fullscreen()
        fullscreen = not fullscreen

    prop new fullscreen: bool
        set
            is_fullscreen = value
            for child in main_box.get_children()
                if child != notebook
                    if value
                        child.hide()
                    else
                        child.show()
            if value
                super.fullscreen()
            else
                super.unfullscreen()
        get
            return is_fullscreen

    def on_destroy()
        Idle.add(quit)

    def on_quit()
        destroy()

    def quit(): bool
        Gtk.main_quit()
        return false
