[indent=4]

uses Gtk


def child_widget_at_path(widget: Widget, indices: array of int): Widget
    for var index in indices
        var container = widget as Container
        widget = container.get_children().nth_data(index) as Widget
    return widget

def new_button_with_stock_image(stock_id: string): Button
    var button = new Button()
    button.set_relief(ReliefStyle.NONE)
    var image = new Image.from_stock(stock_id, ICON_SIZE)
    button.add(image)
    return button

