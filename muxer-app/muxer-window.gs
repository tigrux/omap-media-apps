[indent=4]


const TITLE: string = "Omap4 Muxer"


class Omap.MuxerWindow: Omap.MediaWindow

    enum ComboCol
        GROUP
        PREVIEW
        RECORD

    combo_box: Gtk.ComboBox
    combo_model: Gtk.ListStore
    chooser_button: Gtk.FileChooserButton
    preview_button: Gtk.ToolButton
    record_button: Gtk.ToolButton
    stop_button: Gtk.ToolButton
    muxer_control: Omap.MuxerControl
    video_area: Omap.VideoArea

    debug_dialog: Omap.DebugDialog

    init
        setup_widgets()

    def setup_widgets()
        title = TITLE
        setup_toolbar()
        setup_notebook()
        main_box.show_all()
        video_area.realize()

    def setup_toolbar()
        var chooser_item = new Gtk.ToolItem()
        toolbar.add(chooser_item)
        chooser_item.set_expand(true)
        chooser_button = new Gtk.FileChooserButton( \
            "Config file", Gtk.FileChooserAction.OPEN)
        chooser_item.add(chooser_button)
        chooser_button.file_set += on_chooser_file_set

        var file_filter = new Gtk.FileFilter()
        file_filter.set_name("Config files")
        file_filter.add_pattern("*.ini")
        file_filter.add_pattern("*.xml")
        chooser_button.add_filter(file_filter)

        var combo_item = new Gtk.ToolItem()
        toolbar.add(combo_item)
        var s = typeof(string)
        combo_model = new Gtk.ListStore(3, s, s, s)
        combo_box = new Gtk.ComboBox.with_model(combo_model)
        combo_item.add(combo_box)

        var renderer = new Gtk.CellRendererText()
        combo_box.pack_start(renderer, true)
        combo_box.set_attributes(renderer, "text", ComboCol.GROUP, null)

        toolbar_add_expander()

        preview_button = new Gtk.ToolButton.from_stock(Gtk.STOCK_MEDIA_PLAY)
        toolbar.add(preview_button)
        preview_button.clicked += on_preview

        var pause_button = new Gtk.ToolButton.from_stock(Gtk.STOCK_MEDIA_PAUSE)
        toolbar.add(pause_button)
        pause_button.clicked += on_pause

        record_button = new Gtk.ToolButton.from_stock(Gtk.STOCK_MEDIA_RECORD)
        toolbar.add(record_button)
        record_button.clicked += on_record

        stop_button = new Gtk.ToolButton.from_stock(Gtk.STOCK_MEDIA_STOP)
        toolbar.add(stop_button)
        stop_button.clicked += on_stop

        toolbar_add_expander()

        toolbar_add_quit_button()

    def setup_notebook()
        video_area = new Omap.VideoArea()
        notebook.append_page(video_area, new Gtk.Label("Capture"))

    def setup_control(preview: string, record: string)
        muxer_control = new Omap.MuxerControl(preview, record)
        muxer_control.error_message += on_control_error    
        muxer_control.preview_started += on_preview_started
        muxer_control.preview_stopped += on_preview_stopped
        muxer_control.record_started += on_record_started
        muxer_control.record_stopped += on_record_stopped
        muxer_control.prepare_xwindow_id += def(imagesink)
            video_area.sink = imagesink

        try
            muxer_control.load()
        except e: Error
            Omap.error_dialog(e)
            return

    def on_preview()
        if muxer_control == null
            preview, record: string
            if not get_pipelines(out preview, out record)
                print "Could not get the pipelines"
                return
            setup_control(preview, record)
        muxer_control.start_preview()

    def on_pause()
        if muxer_control == null
            return
        muxer_control.state = Gst.State.PAUSED

    def on_record()
        if muxer_control == null
            return
        if not muxer_control.previewing
            return
        if muxer_control.recording
            return
        try
            muxer_control.start_record()
        except e: Error
            Omap.error_dialog(e)

    def on_stop()
        if muxer_control == null
            return
        if muxer_control.recording
            muxer_control.stop_record()
        else if muxer_control.previewing
            muxer_control.stop_preview()
            muxer_control = null

    def on_chooser_file_set()
        var config_file = chooser_button.get_filename()
        var key_file = new KeyFile()
        try
            if config_file.has_suffix(".ini")
                key_file.load_from_file(config_file, KeyFileFlags.NONE)
            else
                var xml_parser = new MuxerConfigParser()
                xml_parser.parse_file(config_file, ref key_file)
        except e1: FileError
            Omap.error_dialog(e1)
            return
        except e2: KeyFileError
            Omap.error_dialog(e2)
            return
        except e3: MarkupError
            Omap.error_dialog(e3)
            return

        try
            combo_model.clear()
            for group in key_file.get_groups()
                var preview = key_file.get_string(group, "preview")
                var record = key_file.get_string(group, "record")
                if preview == null or record == null
                    continue
                combo_model.insert_with_values( \
                    null, -1, \
                    ComboCol.GROUP, group, \
                    ComboCol.PREVIEW, preview, \
                    ComboCol.RECORD, record, \
                    -1)
        except e4: KeyFileError
            Omap.error_dialog(e4)

    def get_pipelines(out preview: string, out record: string): bool
        iter: Gtk.TreeIter
        if not combo_box.get_active_iter(out iter)
            return false
        combo_model.get(iter, \
            ComboCol.PREVIEW, out preview, \
            ComboCol.RECORD, out record, \
            -1)
        return true

    def on_preview_started()
        print "preview started"

    def on_preview_stopped()
        print "preview stopped"

    def on_record_started()
        print "record started"

    def on_record_stopped()
        print "record stopped"

    def on_control_error(src: Gst.Object, error: Error, debug: string)
        muxer_control.stop()
        show_debug(error, debug)

    def show_debug(error: Error, debug: string)
        setup_debug_dialog()
        debug_dialog.add_error_debug(error, debug)

    def setup_debug_dialog()
        if debug_dialog == null
            debug_dialog = new Omap.DebugDialog(this)
            debug_dialog.closed += on_debug_dialog_closed
            debug_dialog.show_all()

    def on_debug_dialog_closed()
        muxer_control = null
        debug_dialog = null

