[indent=4]


class Omap.MuxerConfigParser: GLib.Object
    current_group: string
    current_key: string
    current_value: string

    context: MarkupParseContext
    config_key_file: unowned KeyFile
    has_preview: bool
    has_record: bool
    const parser: MarkupParser = {start, end, text, null, null}

    init
        context = new MarkupParseContext(parser, 0, this, null)

    def parse_data(data: string,
                   length: ssize_t,
                   ref key_file: KeyFile): bool raises MarkupError
        config_key_file = key_file
        return context.parse(data, length)

    def parse_file(file: string,
                   ref key_file: KeyFile): bool raises MarkupError, FileError
        content: string
        length: size_t
        if FileUtils.get_contents(file, out content, out length)
            return parse_data(content, (ssize_t)length, ref key_file)
        return false

    def start(context: MarkupParseContext,
              name: string,
              attr_names: array of string,
              attr_values: array of string) raises MarkupError
        line_n: int
        char_n: int
        context.get_position(out line_n, out char_n)

        if name == "pipeline"
            current_key = null
            has_preview = false
            has_record = false
            var i = 0
            attr_name: string
            while (attr_name = attr_names[i]) != null
                if attr_name == "name"
                    var attr_value = attr_values[i]
                    if attr_value != null
                        current_group = attr_values[i]
                else
                    raise new MarkupError.UNKNOWN_ATTRIBUTE(
                        "Error on line %d char %d: Element '%s' has unknown attribute '%s'",
                        line_n, char_n, name, attr_name)
                i++
            if current_group == null
                raise new MarkupError.MISSING_ATTRIBUTE(
                    "Error on line %d char %d: Element '%s' has no attribute 'name'",
                    line_n, char_n, name)
        else
            if name == "preview"
                has_preview = true
            else
            if name == "record"
                has_record = true

            if has_preview or has_record
                if current_group != null
                    current_key = name
                else
                    raise new MarkupError.INVALID_CONTENT(
                        "Error on line %d char %d: Element '%s' was opened, but no outer element 'pipeline' was found",
                        line_n, char_n, name)
            else
                raise new MarkupError.UNKNOWN_ELEMENT(
                    "Error on line %d char %d: Element '%s' in unknown",
                    line_n, char_n, name)

    def end(context: MarkupParseContext, name: string ) raises MarkupError
        line_n: int
        char_n: int
        context.get_position(out line_n, out char_n)

        if name == "pipeline"
            current_group = null
            missing_tag: string
            if not has_preview
                missing_tag = "preview"
            else if not has_record
                missing_tag = "record"
            else
                missing_tag = null
            if missing_tag != null
                raise new MarkupError.INVALID_CONTENT(
                    "Error on line %d char %d: Element '%s' was closed, but no inner element '%s' was found",
                    line_n, char_n, name, missing_tag)
        else
        if name == "preview" or name == "record"
            if normalize_value()
                config_key_file.set_string(
                    current_group, current_key, current_value)
                current_key = null
            else
                raise new MarkupError.INVALID_CONTENT(
                    "Error on line %d char %d: Element '%s' has no text",
                    line_n, char_n, name)

    def normalize_value(): bool
        if current_value == null
            return false
        var stripped_list = new GLib.List of string
        lines: array of string
        i: int
        lines = current_value.split("\n")
        i = 0
        line: string
        while (line = lines[i]) != null
            if line.length > 0
                stripped_list.append(line)
            i++
        lines = new array of string [stripped_list.length()]
        i = 0
        for line in stripped_list
            lines[i] = line
            i++
        current_value = string.joinv(" ", lines)
        if current_value.length == 0
            return false
        return true

    def text(context: MarkupParseContext,
             text: string, text_len: size_t) raises MarkupError
        if current_group != null and current_key != null
            current_value = text

