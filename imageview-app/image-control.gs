[indent=4]


const IMAGE_PIPELINE_DESC: string = \
"filesrc name=filesrc ! jpegdec ! ffmpegcolorspace ! ximagesink"


class Omap.ImageControl: Omap.MediaControl
    filesrc: dynamic Gst.Element

    prop location: string
        set
            filesrc.location = value

    construct() raises Error
        setup_pipeline()

    def setup_pipeline() raises Error
        var image_pipeline = Gst.parse_launch(IMAGE_PIPELINE_DESC) as Gst.Pipeline
        image_pipeline.name = "image_pipeline"
        if (filesrc = image_pipeline.get_by_name("filesrc")) == null
            raise new Gst.CoreError.FAILED( \
                        "No element named filesrc in the image pipeline")
        pipeline = image_pipeline

