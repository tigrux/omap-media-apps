[indent=4]

uses Gtk


const TITLE: string = "Omap4 Muxer"
const ICON: string = "omap4-muxer-app"


class MuxerWindow: MediaWindow

    enum ComboCol
        GROUP
        PREVIEW
        RECORD

    combo_box: ComboBox
    combo_model: ListStore
    chooser_button: FileChooserButton
    preview_button: ToolButton
    record_button: ToolButton
    probe_button: ToggleToolButton
    stop_button: ToolButton
    muxer_control: MuxerControl
    video_area: VideoArea

    debug_dialog: DebugDialog

    init
        setup_widgets()

    def setup_widgets()
        set_title(TITLE)
        lookup_and_set_icon_name(ICON)
        setup_toolbar()
        setup_notebook()
        main_box.show_all()
        video_area.realize()

    def setup_toolbar()
        var chooser_item = new ToolItem()
        toolbar.add(chooser_item)
        chooser_item.set_expand(true)
        chooser_button = new FileChooserButton( \
            "Config file", FileChooserAction.OPEN)
        chooser_item.add(chooser_button)
        chooser_button.file_set += on_chooser_file_set

        var file_filter = new FileFilter()
        file_filter.set_name("Config files")
        file_filter.add_pattern("*.ini")
        file_filter.add_pattern("*.xml")
        chooser_button.add_filter(file_filter)

        var combo_item = new ToolItem()
        toolbar.add(combo_item)
        var s = typeof(string)
        combo_model = new ListStore(3, s, s, s)
        combo_box = new ComboBox.with_model(combo_model)
        combo_item.add(combo_box)

        var renderer = new CellRendererText()
        combo_box.pack_start(renderer, true)
        combo_box.set_attributes(renderer, "text", ComboCol.GROUP, null)
        combo_box.changed += on_combo_changed

        toolbar_add_expander()

        preview_button = new ToolButton.from_stock(STOCK_MEDIA_PLAY)
        toolbar.add(preview_button)
        preview_button.clicked += on_preview

        record_button = new ToolButton.from_stock(STOCK_MEDIA_RECORD)
        toolbar.add(record_button)
        record_button.clicked += on_record

        stop_button = new ToolButton.from_stock(STOCK_MEDIA_STOP)
        toolbar.add(stop_button)
        stop_button.clicked += on_stop

        toolbar_add_expander()

        probe_button = new ToggleToolButton.from_stock(STOCK_CONVERT)
        toolbar.add(probe_button)

        toolbar_add_quit_button()

    def setup_notebook()
        video_area = new VideoArea()
        notebook.append_page(video_area, new Label("Capture"))

    def on_combo_changed()
        preview: string
        record: string
        if not get_pipelines(out preview, out record)
            print "Could not get the pipelines"
            return
        muxer_control = new MuxerControl(preview, record)
        muxer_control.error_message += on_control_error
        try
            muxer_control.load()
        except e: Error
            error_dialog(e)
            return
        video_area.set_control(muxer_control)
        muxer_control.eos_message += record_stopped

    def on_preview()
        if muxer_control == null
            return
        if muxer_control.previewing
            return
        if muxer_control.recording
            return
        muxer_control.start_preview()

    def on_record()
        if muxer_control == null
            return
        if not muxer_control.previewing
            return
        if muxer_control.recording
            return
        muxer_control.buffer_probe_enabled = probe_button.get_active()
        try
            muxer_control.start_record()
        except e: Error
            error_dialog(e)

    def on_stop()
        if muxer_control == null
            return
        if muxer_control.recording
            muxer_control.stop_record()
        else if muxer_control.previewing
            muxer_control.stop_preview()

    def record_stopped()
        pass

    def on_chooser_file_set()
        var config_file = chooser_button.get_filename()
        var key_file = new KeyFile()
        try
            if config_file.has_suffix(".ini")
                key_file.load_from_file(config_file, KeyFileFlags.NONE)
            else
                var xml_parser = new MuxerConfigParser()
                xml_parser.parse_file(config_file, ref key_file)
        except e: FileError
            error_dialog(e)
            return
        except e: KeyFileError
            error_dialog(e)
            return
        except e: MarkupError
            error_dialog(e)
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
        except e: KeyFileError
            error_dialog(e)

    def get_pipelines(out preview: string, out record: string): bool
        iter: TreeIter
        if not combo_box.get_active_iter(out iter)
            return false
        combo_model.get(iter, \
            ComboCol.PREVIEW, out preview, \
            ComboCol.RECORD, out record, \
            -1)
        return true

    def on_control_error(src: Gst.Object, error: Error, debug: string)
        show_debug(error, debug)

    def show_debug(error: Error, debug: string)
        setup_debug_dialog()
        debug_dialog.add_error_debug(error, debug)

    def setup_debug_dialog()
        if debug_dialog == null
            debug_dialog = new DebugDialog(this)
            debug_dialog.closed += on_debug_dialog_closed
            debug_dialog.show_all()

    def on_debug_dialog_closed()
        muxer_control = null
        debug_dialog = null

