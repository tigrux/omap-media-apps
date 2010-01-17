[indent=4]

uses Gtk


def new_expander(): ToolItem
    var expander_item = new SeparatorToolItem()
    expander_item.set_expand(true)
    expander_item.set_draw(false)
    return expander_item

