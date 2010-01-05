[indent=4]

uses Gtk


class ErrorDialog: Window
    text_buffer: TextBuffer

    event closed()

    init
        set_title("Error")
        var box = new_error_box()
        add(box)
        text_buffer.create_tag("bold", "weight", Pango.Weight.BOLD, null)

    def add_error_with_debug(error: Error, debug: string)
        iter: TextIter
        text_buffer.get_end_iter(out iter)
        text_insert_new_line(ref iter)
        text_buffer.insert_with_tags_by_name(iter, \
            error.message, -1, "bold", null)
        text_insert_new_line(ref iter)
        text_buffer.insert(iter, debug, -1)
        text_insert_new_line(ref iter)

    def text_insert_new_line(ref iter: TextIter)
        text_buffer.insert(iter, "\n", -1)

    def new_error_box(): Box
        var box = new VBox(false, 6)

        var scrolled_window = new ScrolledWindow(null, null)
        box.pack_start(scrolled_window, true, true, 0)
        scrolled_window.set_policy(PolicyType.AUTOMATIC, PolicyType.AUTOMATIC)

        var text_view = new TextView()
        text_view.set_editable(false)
        text_view.set_cursor_visible(false)
        text_view.set_wrap_mode(WrapMode.WORD)
        text_buffer = text_view.get_buffer()
        scrolled_window.add(text_view)

        var button_box = new HButtonBox()
        box.pack_start(button_box, false, false, 6)
        button_box.set_layout(ButtonBoxStyle.END)
        var close_button = new_button_with_stock_image(STOCK_CLOSE)
        button_box.add(close_button)
        close_button.clicked += def()
            closed()

        box.show_all()
        return box

