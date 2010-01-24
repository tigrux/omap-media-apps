[indent=4]


class Omap.DebugDialog: Gtk.Dialog
    text_buffer: Gtk.TextBuffer
    errors_n: int

    event closed()

    init
        title = "Error"
        modal = true
        add_button(Gtk.STOCK_CLOSE, -1)
        var content_area = get_content_area() as Gtk.Box
        content_area.add(new_error_box())
        text_buffer.create_tag("bold", "weight", Pango.Weight.BOLD, null)
        response += def()
            closed()
            destroy()
        delete_event += def()
            closed()

    construct(parent: Gtk.Window)
        width, height: int
        parent.get_size(out width, out height)
        set_default_size(3*width/4, 3*height/4)
        set_transient_for(parent)

    def add_error_debug(error: Error, debug: string)
        errors_n ++
        if errors_n > 1
            title = "%d errors".printf(errors_n)
        iter: Gtk.TextIter
        text_buffer.get_end_iter(out iter)
        text_insert_new_line(ref iter)
        text_buffer.insert_with_tags_by_name(iter, \
            error.message, -1, "bold", null)
        text_insert_new_line(ref iter)
        if debug != null
            text_buffer.insert(iter, debug, -1)
            text_insert_new_line(ref iter)

    def text_insert_new_line(ref iter: Gtk.TextIter)
        text_buffer.insert(iter, "\n", -1)

    def new_error_box(): Gtk.Box
        var box = new Gtk.HBox(false, 0)

        var image = new Gtk.Image.from_stock( \
                        Gtk.STOCK_DIALOG_ERROR, Gtk.IconSize.DIALOG)
        box.pack_start(image, false, false, 3)

        var separator = new Gtk.VSeparator()
        box.pack_start(separator, false, false, 0)

        var scrolled_window = new Gtk.ScrolledWindow(null, null)
        box.pack_start(scrolled_window, true, true, 0)
        var policy = Gtk.PolicyType.AUTOMATIC
        scrolled_window.set_policy(policy, policy)

        var text_view = new Gtk.TextView()
        scrolled_window.add(text_view)
        text_view.editable = false
        text_view.cursor_visible = false
        text_view.wrap_mode = Gtk.WrapMode.WORD
        text_buffer = text_view.buffer

        box.show_all()
        return box

namespace Omap
    def error_dialog(error: Error)
        dialog: Gtk.Dialog = new Gtk.MessageDialog( \
            null, 0, \
            Gtk.MessageType.ERROR,  Gtk.ButtonsType.CLOSE, \
            "%s", error.message)
        dialog.title = "Error"
        dialog.response += def(widget, response)
            if widget != null
                widget.destroy()
        dialog.run()

