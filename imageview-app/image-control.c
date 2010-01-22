/* image-control.c generated by valac, the Vala compiler
 * generated from image-control.gs, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <common.h>
#include <gst/gst.h>
#include <stdlib.h>
#include <string.h>


#define TYPE_IMAGE_CONTROL (image_control_get_type ())
#define IMAGE_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_IMAGE_CONTROL, ImageControl))
#define IMAGE_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_IMAGE_CONTROL, ImageControlClass))
#define IS_IMAGE_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_IMAGE_CONTROL))
#define IS_IMAGE_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_IMAGE_CONTROL))
#define IMAGE_CONTROL_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_IMAGE_CONTROL, ImageControlClass))

typedef struct _ImageControl ImageControl;
typedef struct _ImageControlClass ImageControlClass;
typedef struct _ImageControlPrivate ImageControlPrivate;
#define _gst_object_unref0(var) ((var == NULL) ? NULL : (var = (gst_object_unref (var), NULL)))

struct _ImageControl {
	MediaControl parent_instance;
	ImageControlPrivate * priv;
	GstElement* filesrc;
};

struct _ImageControlClass {
	MediaControlClass parent_class;
};


static gpointer image_control_parent_class = NULL;

#define IMAGE_PIPELINE_DESC "filesrc name=filesrc ! jpegdec ! ffmpegcolorspace ! ximagesink"
GType image_control_get_type (void);
enum  {
	IMAGE_CONTROL_DUMMY_PROPERTY,
	IMAGE_CONTROL_LOCATION
};
void image_control_setup_pipeline (ImageControl* self, GError** error);
ImageControl* image_control_new (GError** error);
ImageControl* image_control_construct (GType object_type, GError** error);
static inline void _dynamic_set_location2 (GstElement* obj, const char* value);
void image_control_set_location (ImageControl* self, const char* value);
static void image_control_finalize (GObject* obj);
static void image_control_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);



ImageControl* image_control_construct (GType object_type, GError** error) {
	GError * _inner_error_;
	ImageControl * self;
	_inner_error_ = NULL;
	self = (ImageControl*) media_control_construct (object_type);
	image_control_setup_pipeline (self, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return NULL;
	}
	return self;
}


ImageControl* image_control_new (GError** error) {
	return image_control_construct (TYPE_IMAGE_CONTROL, error);
}


void image_control_setup_pipeline (ImageControl* self, GError** error) {
	GError * _inner_error_;
	GstElement* _tmp0_;
	GstElement* _tmp1_;
	GstPipeline* image_pipeline;
	GstElement* _tmp2_;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	_tmp0_ = gst_parse_launch (IMAGE_PIPELINE_DESC, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	image_pipeline = (_tmp1_ = _tmp0_, GST_IS_PIPELINE (_tmp1_) ? ((GstPipeline*) _tmp1_) : NULL);
	gst_object_set_name ((GstObject*) image_pipeline, "image_pipeline");
	if ((self->filesrc = (_tmp2_ = gst_bin_get_by_name ((GstBin*) image_pipeline, "filesrc"), _gst_object_unref0 (self->filesrc), _tmp2_)) == NULL) {
		_inner_error_ = g_error_new_literal (GST_CORE_ERROR, GST_CORE_ERROR_FAILED, "No element named filesrc in the image pipeline");
		if (_inner_error_ != NULL) {
			g_propagate_error (error, _inner_error_);
			_gst_object_unref0 (image_pipeline);
			return;
		}
	}
	media_control_set_pipeline ((MediaControl*) self, (GstBin*) image_pipeline);
	_gst_object_unref0 (image_pipeline);
}


static inline void _dynamic_set_location2 (GstElement* obj, const char* value) {
	g_object_set (obj, "location", value, NULL);
}


void image_control_set_location (ImageControl* self, const char* value) {
	g_return_if_fail (self != NULL);
	_dynamic_set_location2 (self->filesrc, value);
	g_object_notify ((GObject *) self, "location");
}


static void image_control_class_init (ImageControlClass * klass) {
	image_control_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->set_property = image_control_set_property;
	G_OBJECT_CLASS (klass)->finalize = image_control_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), IMAGE_CONTROL_LOCATION, g_param_spec_string ("location", "location", "location", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_WRITABLE));
}


static void image_control_instance_init (ImageControl * self) {
}


static void image_control_finalize (GObject* obj) {
	ImageControl * self;
	self = IMAGE_CONTROL (obj);
	{
		if (media_control_get_pipeline ((MediaControl*) self) != NULL) {
			gst_element_set_state ((GstElement*) media_control_get_pipeline ((MediaControl*) self), GST_STATE_NULL);
		}
	}
	_gst_object_unref0 (self->filesrc);
	G_OBJECT_CLASS (image_control_parent_class)->finalize (obj);
}


GType image_control_get_type (void) {
	static GType image_control_type_id = 0;
	if (image_control_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (ImageControlClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) image_control_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (ImageControl), 0, (GInstanceInitFunc) image_control_instance_init, NULL };
		image_control_type_id = g_type_register_static (TYPE_MEDIA_CONTROL, "ImageControl", &g_define_type_info, 0);
	}
	return image_control_type_id;
}


static void image_control_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	ImageControl * self;
	self = IMAGE_CONTROL (object);
	switch (property_id) {
		case IMAGE_CONTROL_LOCATION:
		image_control_set_location (self, g_value_get_string (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}




