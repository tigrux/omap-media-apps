[indent=4]

uses Gtk


class DebugDialog: Dialog
    text_buffer: TextBuffer
    errors_n: int

    event closed()

    init
        set_title("Error")
        add_button(STOCK_CLOSE, -1)
        set_modal(true)
        var content_area = get_content_area() as Box
        content_area.add(new_error_box())
        text_buffer.create_tag("bold", "weight", Pango.Weight.BOLD, null)
        response += def()
            closed()
            destroy()
        delete_event += def()
            closed()

    construct(parent: Window)
        width, height: int
        parent.get_size(out width, out height)
        set_default_size(3*width/4, 3*height/4)
        set_transient_for(parent)

    def add_error_debug(error: Error, debug: string)
        errors_n ++
        if errors_n > 1
            set_title("%d errors".printf(errors_n))
        iter: TextIter
        text_buffer.get_end_iter(out iter)
        text_insert_new_line(ref iter)
        text_buffer.insert_with_tags_by_name(iter, \
            error.message, -1, "bold", null)
        text_insert_new_line(ref iter)
        if debug != null
            text_buffer.insert(iter, debug, -1)
            text_insert_new_line(ref iter)

    def text_insert_new_line(ref iter: TextIter)
        text_buffer.insert(iter, "\n", -1)

    def new_error_box(): Box
        var box = new HBox(false, 0)

        var image = new Image.from_stock(STOCK_DIALOG_ERROR, IconSize.DIALOG)
        box.pack_start(image, false, false, 3)

        var separator = new VSeparator()
        box.pack_start(separator, false, false, 0)

        var scrolled_window = new ScrolledWindow(null, null)
        box.pack_start(scrolled_window, true, true, 0)
        scrolled_window.set_policy(PolicyType.AUTOMATIC, PolicyType.AUTOMATIC)

        var text_view = new TextView()
        scrolled_window.add(text_view)
        text_view.set_editable(false)
        text_view.set_cursor_visible(false)
        text_view.set_wrap_mode(WrapMode.WORD)
        text_buffer = text_view.get_buffer()

        box.show_all()
        return box

def error_dialog(error: Error)
    dialog: Dialog = new MessageDialog( \
        null, 0, \
        MessageType.ERROR,  ButtonsType.CLOSE, \
        "%s", error.message)
    dialog.set_title("Error")
    dialog.response += def(widget, response)
        if widget != null
            widget.destroy()
    dialog.run()


