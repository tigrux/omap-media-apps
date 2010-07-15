[indent=4]


class Omap.PlayListControl: Omap.MediaControl
    enum Col
        ICON
        TITLE
        ARTIST
        ALBUM
        FILE

    playlist_store: Gtk.ListStore
    current_row: Gtk.TreePath
    number_of_rows: int
    player: dynamic Gst.Bin

    prop volume: double
        get
            return player.volume
        set
            player.volume = value

    prop n_rows: uint
        get
            return number_of_rows

    prop location: string
        set
            player.uri = "file://%s".printf(value)

    event playing(iter: Gtk.TreeIter)
    event paused(iter: Gtk.TreeIter)
    event stopped(iter: Gtk.TreeIter)
    event moved(iter: Gtk.TreeIter)
    event title_changed(title: string)

    init
        tag_found.connect(on_tag_found)
        player = Gst.ElementFactory.make("playbin2", "player") as Gst.Bin
        if player == null
            player = Gst.ElementFactory.make("playbin", "player") as Gst.Bin
        else
            ((GLib.Object)player).set("flags", 0x67)
        pipeline = player

    construct(store: Gtk.ListStore)
        playlist_store = store
        playlist_store.row_inserted.connect(on_row_inserted)
        playlist_store.row_deleted.connect(on_row_deleted)

    def play(): bool
        iter: Gtk.TreeIter
        if not get_iter(out iter)
            return false

        filename: string
        playlist_store.get(iter, Col.FILE, out filename, -1)

        if state == Gst.State.NULL
            location = filename

        if pipeline.set_state(Gst.State.PLAYING) != Gst.StateChangeReturn.FAILURE
            playlist_store.set(iter, Col.ICON, Gtk.STOCK_MEDIA_PLAY, -1)
            title_changed(iter_get_title(iter))
            playing(iter)
            return true
        return false

    def pause(): bool
        if pipeline.set_state(Gst.State.PAUSED) != Gst.StateChangeReturn.FAILURE
            iter: Gtk.TreeIter
            if get_iter(out iter)
                playlist_store.set(iter,
                    Col.ICON, Gtk.STOCK_MEDIA_PAUSE, -1)
            paused(iter)
            return true
        return false

    def stop(): bool
        if pipeline.set_state(Gst.State.NULL) != Gst.StateChangeReturn.FAILURE
            iter: Gtk.TreeIter
            if get_iter(out iter)
                playlist_store.set(iter, Col.ICON, null, -1)
            stopped(iter)
            return true
        return false

    def prev(): bool
        if current_row == null
            return false
        stop()
        if current_row.prev()
            return move_to(current_row)
        return false

    def next(): bool
        if current_row == null
            return false
        stop()
        var row_index = current_row.get_indices()[0]
        if row_index < number_of_rows - 1
            current_row.next()
            return move_to(current_row)
        return false

    def add_file(file: string)
        playlist_store.insert_with_values(
            null, -1,
            Col.TITLE, Filename.display_basename(file),
            Col.FILE, file,
            -1)

    def move_to(row: Gtk.TreePath): bool
        iter: Gtk.TreeIter
        if playlist_store.get_iter(out iter, row)
            current_row = row
            moved(iter)
            return true
        return false

    def get_iter(out iter: Gtk.TreeIter): bool
        if current_row == null
            return false
        if not playlist_store.get_iter(out iter, current_row)
            return false
        return true

    def on_row_deleted(row: Gtk.TreePath)
        number_of_rows --
        if current_row == null
            return
        if current_row.compare(row) == 0
            stop()

    def on_tag_found(tag_name: string, tag_value: GLib.Value)
        column: Col
        is_title: bool = false
        case tag_name
            when Gst.TAG_TITLE
                column = Col.TITLE
                is_title = true
            when Gst.TAG_ARTIST
                column = Col.ARTIST
            when Gst.TAG_ALBUM
                column = Col.ALBUM
            default
                return

        var column_value = tag_value.get_string()
        iter: Gtk.TreeIter
        playlist_store.get_iter(out iter, current_row)
        playlist_store.set(
            iter,
            column, column_value,
            -1)
        if is_title
           title_changed(column_value)

    def on_row_inserted(row: Gtk.TreePath)
        number_of_rows ++

    def static get_icon_column(): int
        return Col.ICON

    def static get_title_column(): int
        return Col.TITLE

    def static get_artist_column(): int
        return Col.ARTIST

    def static get_album_column(): int
        return Col.ALBUM

    def iter_get_title(iter: Gtk.TreeIter): string
        name: string
        playlist_store.get(iter, Col.TITLE, out name, -1)
        return name

    def iter_get_file(iter: Gtk.TreeIter): string
        file: string
        playlist_store.get(iter, Col.FILE, out file, -1)
        return file

    def static model_new(): Gtk.ListStore
        var s = typeof(string)
        return new Gtk.ListStore(5, s, s, s, s, s)

