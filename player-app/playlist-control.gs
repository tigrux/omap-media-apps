[indent=4]

uses Gtk
uses Gst


class PlayListControl: GLib.Object implements Control
    enum Col
        ICON
        NAME
        FILE

    player: Element
    playlist_store: ListStore
    current_row: TreePath
    number_of_rows: int

    prop pipeline: Element
        get
            return player

    prop volume: double
        get
            value: double
            player.get("volume", out value, null)
            return value
        set
            player.set("volume", value, null)

    prop n_rows: uint
        get
            return number_of_rows

    event eos()
    event error(e: Error, debug: string)
    event playing(iter: TreeIter)
    event paused(iter: TreeIter)
    event stopped(iter: TreeIter)
    event moved(iter: TreeIter)

    init
        player = ElementFactory.make("playbin2", "player")
        if player == null
            player = ElementFactory.make("playbin", "player")
        var bus = player.get_bus()
        bus.add_signal_watch()
        bus.message += on_bus_message

    construct(store: ListStore)
        playlist_store = store
        playlist_store.row_inserted += on_row_inserted
        playlist_store.row_deleted += on_row_deleted

    def set_location(location: string)
        player.set("uri", "file://%s".printf(location), null)

    def get_bus(): Bus
        return player.get_bus()

    def get_position(): int64
        var format = Format.TIME
        position: int64
        player.query_position(ref format, out position)
        return position

    def get_duration(): int64
        var format = Format.TIME
        duration: int64
        player.query_duration(ref format, out duration)
        return duration

    def play(): bool
        iter: TreeIter
        if not get_iter(out iter)
            return false

        filename: string
        playlist_store.get(iter, Col.FILE, out filename, -1)

        var state = get_state()
        if state == State.NULL
            set_location(filename)

        if player.set_state(State.PLAYING) != StateChangeReturn.FAILURE
            playlist_store.set(iter, Col.ICON, STOCK_MEDIA_PLAY, -1)
            playing(iter)
            return true
        return false

    def pause(): bool
        if player.set_state(State.PAUSED) != StateChangeReturn.FAILURE
            iter: TreeIter
            if get_iter(out iter)
                playlist_store.set(iter, \
                    Col.ICON, STOCK_MEDIA_PAUSE, -1)
            paused(iter)
            return true
        return false

    def stop(): bool
        if player.set_state(State.NULL) != StateChangeReturn.FAILURE
            iter: TreeIter
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
        playlist_store.insert_with_values( \
            null, -1, \
            Col.NAME, Filename.display_basename(file), \
            Col.FILE, file, \
            -1)

    def seek(location: int64)
        var seek_event = new Event.seek( \
            1.0, Format.TIME, \
            SeekFlags.FLUSH | SeekFlags.ACCURATE, \
            Gst.SeekType.SET, location, \
            Gst.SeekType.NONE, 0)
        player.send_event(seek_event)

    def get_state(): Gst.State
        state: State
        player.get_state(out state, null, (ClockTime)(MSECOND*50))
        return state

    def move_to(row: TreePath): bool
        iter: TreeIter
        if playlist_store.get_iter(out iter, row)
            current_row = row
            moved(iter)
            return true
        return false

    def get_iter(out iter: TreeIter): bool
        if current_row == null
            return false
        if not playlist_store.get_iter(out iter, current_row)
            return false
        return true

    def on_row_deleted(row: TreePath)
        number_of_rows --
        if current_row == null
            return
        if current_row.compare(row) == 0
            stop()

    def on_row_inserted(row: TreePath)
        number_of_rows ++

    def on_bus_message(message: Message)
        case message.type
            when Gst.MessageType.EOS
                eos()
            when Gst.MessageType.ERROR
                e: Error
                debug: string
                message.parse_error(out e, out debug)
                error(e, debug)
            default
                pass

    def static get_name_column(): int
        return Col.NAME

    def static get_icon_column(): int
        return Col.ICON

    def iter_get_name(iter: TreeIter): string
        name: string
        playlist_store.get(iter, Col.NAME, out name, -1)
        return name

    def iter_get_file(iter: TreeIter): string
        file: string
        playlist_store.get(iter, Col.FILE, out file, -1)
        return file

