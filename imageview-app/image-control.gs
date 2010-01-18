[indent=4]

uses Gst
uses Gtk


const IMAGE_PIPELINE_DESC: string = \
"filesrc name=filesrc ! jpegdec ! ffmpegcolorspace ! ximagesink"

class ImageControl: MediaControl
    filesrc: dynamic Element

    prop location: string
        set
            filesrc.location = value

    construct() raises Error
        setup_pipeline()

    def setup_pipeline() raises Error
        var image_pipeline = parse_launch(IMAGE_PIPELINE_DESC) as Pipeline
        image_pipeline.set_name("image_pipeline")
        if (filesrc = image_pipeline.get_by_name("filesrc")) == null
            raise new CoreError.FAILED( \
                        "No element named filesrc in the image pipeline")
        set_pipeline(image_pipeline)

