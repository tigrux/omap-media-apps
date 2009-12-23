[indent=4]

uses Gtk


const TITLE: string = "MuxerApp"
const ICON_SIZE: IconSize = IconSize.DND
const USE_BUFFER_PROBE: bool = false

enum MuxerComboCol
    GROUP
    PREVIEW
    RECORD


class MuxerWindow: Window

    combo_box: ComboBox
    combo_model: ListStore
    chooser_button: FileChooserButton
    record_button: Button
    quit_button: Button
    probe_button: ToggleButton
    stop_button: Button
    muxer_control: MuxerControl
    video_area: VideoArea

    init
        set_default_size(800, 480)
        destroy += on_quit

        var main_box = new VBox(false, 6)
        add(main_box)

        var buttons_box = new HBox(false, 6)
        main_box.pack_start(buttons_box, false, false, 0)

        chooser_button = new FileChooserButton( \
            "Config file", FileChooserAction.OPEN)
        buttons_box.pack_start(chooser_button, true, true, 0)
        chooser_button.file_set += on_chooser_file_set

        var file_filter = new FileFilter()
        file_filter.set_name("Config files")
        file_filter.add_pattern("*.ini")
        file_filter.add_pattern("*.xml")
        chooser_button.add_filter(file_filter)

        var s = typeof(string)
        combo_model = new ListStore(3, s, s, s)
        combo_box = new ComboBoxEntry.with_model(combo_model, MuxerComboCol.GROUP)
        buttons_box.pack_start(combo_box, false, false, 0)
        var combo_box_child = combo_box.child as Entry
        combo_box_child.button_press_event += on_combo_box_child_pressed
        combo_box_child.set_editable(false)
        combo_box.changed += on_combo_changed

        record_button = new Button()
        buttons_box.pack_start(record_button, false, false, 0)
        record_button.set_sensitive(false)
        record_button.clicked += on_record
        var record_image = new Image()
        record_button.add(record_image)
        record_image.set_from_stock(STOCK_MEDIA_RECORD, ICON_SIZE)

        probe_button = new ToggleButton()
        buttons_box.pack_start(probe_button, false, false, 0)
        var probe_image = new Image()
        probe_button.add(probe_image)
        probe_image.set_from_stock(STOCK_CONVERT, ICON_SIZE)

        stop_button = new Button()
        buttons_box.pack_start(stop_button, false, false, 0)
        stop_button.set_sensitive(false)
        stop_button.clicked += on_stop
        var stop_image = new Image()
        stop_button.add(stop_image)
        stop_image.set_from_stock(STOCK_MEDIA_STOP, ICON_SIZE)

        quit_button = new Button()
        buttons_box.pack_start(quit_button, false, false, 0)
        quit_button.clicked += on_quit
        var quit_image = new Image()
        quit_button.add(quit_image)
        quit_image.set_from_stock(STOCK_QUIT, ICON_SIZE)

        video_area = new VideoArea()
        main_box.pack_start(video_area, true, true, 6)

        main_box.show_all()
        video_area.realize()

    def on_combo_box_child_pressed(event: Gdk.EventButton): bool
        iter: TreeIter
        if combo_model.get_iter_first(out iter)
            combo_box.popup()
        return true

    def on_combo_changed()
        preview: string
        record: string
        if not get_pipelines(out preview, out record)
            print "Could not get the pipelines"
            return
        shutdown()
        muxer_control = new MuxerControl(preview, record)
        muxer_control.enable_buffer_probe(probe_button.get_active())
        try
            muxer_control.load()
        except e: Error
            print e.message
            return
        var bus = muxer_control.get_bus()
        video_area.set_bus(bus)
        muxer_control.start_preview()
        muxer_control.eos += record_stopped
        record_button.set_sensitive(true)

    def on_record()
        try
            muxer_control.start_record()
            stop_button.set_sensitive(true)
            record_button.set_sensitive(false)
            quit_button.set_sensitive(false)
        except e: Error
            print e.message

    def on_stop()
        muxer_control.stop_record()
        stop_button.set_sensitive(false)

    def record_stopped()
        quit_button.set_sensitive(true)
        record_button.set_sensitive(true)

    def on_quit()
        shutdown()
        Gtk.main_quit()

    def shutdown()
        if muxer_control == null
            return
        muxer_control.shutdown()
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
        except e: FileError
            print e.message
            return
        except e: KeyFileError
            print e.message
            return
        except e: MarkupError
            print e.message
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
                    MuxerComboCol.GROUP, group, \
                    MuxerComboCol.PREVIEW, preview, \
                    MuxerComboCol.RECORD, record, \
                    -1)
        except e: KeyFileError
            print e.message

    def get_pipelines(out preview: string, out record: string): bool
        iter: TreeIter
        if not combo_box.get_active_iter(out iter)
            return false
        combo_model.get(iter, \
            MuxerComboCol.PREVIEW, out preview, \
            MuxerComboCol.RECORD, out record, \
            -1)
        return true

