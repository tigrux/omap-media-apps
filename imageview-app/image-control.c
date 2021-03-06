/* image-control.c generated by valac 0.10.0, the Vala compiler
 * generated from image-control.gs, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <common.h>
#include <gst/gst.h>


#define OMAP_TYPE_IMAGE_CONTROL (omap_image_control_get_type ())
#define OMAP_IMAGE_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), OMAP_TYPE_IMAGE_CONTROL, OmapImageControl))
#define OMAP_IMAGE_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), OMAP_TYPE_IMAGE_CONTROL, OmapImageControlClass))
#define OMAP_IS_IMAGE_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), OMAP_TYPE_IMAGE_CONTROL))
#define OMAP_IS_IMAGE_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), OMAP_TYPE_IMAGE_CONTROL))
#define OMAP_IMAGE_CONTROL_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), OMAP_TYPE_IMAGE_CONTROL, OmapImageControlClass))

typedef struct _OmapImageControl OmapImageControl;
typedef struct _OmapImageControlClass OmapImageControlClass;
typedef struct _OmapImageControlPrivate OmapImageControlPrivate;
#define _gst_object_unref0(var) ((var == NULL) ? NULL : (var = (gst_object_unref (var), NULL)))
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))

struct _OmapImageControl {
	OmapMediaControl parent_instance;
	OmapImageControlPrivate * priv;
	GstElement* filesrc;
};

struct _OmapImageControlClass {
	OmapMediaControlClass parent_class;
};


static gpointer omap_image_control_parent_class = NULL;

#define IMAGE_PIPELINE_DESC "filesrc name=filesrc ! jpegdec ! ffmpegcolorspace ! ximagesink"
GType omap_image_control_get_type (void) G_GNUC_CONST;
enum  {
	OMAP_IMAGE_CONTROL_DUMMY_PROPERTY,
	OMAP_IMAGE_CONTROL_LOCATION
};
OmapImageControl* omap_image_control_new (GError** error);
OmapImageControl* omap_image_control_construct (GType object_type, GError** error);
void omap_image_control_setup_pipeline (OmapImageControl* self, GError** error);
void omap_image_control_set_location (OmapImageControl* self, const char* value);
static inline void _dynamic_set_location2 (GstElement* obj, const char* value);
static void omap_image_control_finalize (GObject* obj);
static void omap_image_control_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);



OmapImageControl* omap_image_control_construct (GType object_type, GError** error) {
	OmapImageControl * self;
	GError * _inner_error_ = NULL;
	self = (OmapImageControl*) omap_media_control_construct (object_type);
	omap_image_control_setup_pipeline (self, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		_g_object_unref0 (self);
		return NULL;
	}
	return self;
}


OmapImageControl* omap_image_control_new (GError** error) {
	return omap_image_control_construct (OMAP_TYPE_IMAGE_CONTROL, error);
}


void omap_image_control_setup_pipeline (OmapImageControl* self, GError** error) {
	GstElement* _tmp0_;
	GstElement* _tmp1_;
	GstPipeline* image_pipeline;
	GstElement* _tmp2_;
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = gst_parse_launch (IMAGE_PIPELINE_DESC, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	image_pipeline = (_tmp1_ = _tmp0_, GST_IS_PIPELINE (_tmp1_) ? ((GstPipeline*) _tmp1_) : NULL);
	gst_object_set_name ((GstObject*) image_pipeline, "image_pipeline");
	if ((self->filesrc = (_tmp2_ = gst_bin_get_by_name ((GstBin*) image_pipeline, "filesrc"), _gst_object_unref0 (self->filesrc), _tmp2_)) == NULL) {
		_inner_error_ = g_error_new_literal (GST_CORE_ERROR, GST_CORE_ERROR_FAILED, "No element named filesrc in the image pipeline");
		{
			g_propagate_error (error, _inner_error_);
			_gst_object_unref0 (image_pipeline);
			return;
		}
	}
	omap_media_control_set_pipeline ((OmapMediaControl*) self, (GstBin*) image_pipeline);
	_gst_object_unref0 (image_pipeline);
}


static inline void _dynamic_set_location2 (GstElement* obj, const char* value) {
	g_object_set (obj, "location", value, NULL);
}


void omap_image_control_set_location (OmapImageControl* self, const char* value) {
	g_return_if_fail (self != NULL);
	_dynamic_set_location2 (self->filesrc, value);
	g_object_notify ((GObject *) self, "location");
}


static void omap_image_control_class_init (OmapImageControlClass * klass) {
	omap_image_control_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->set_property = omap_image_control_set_property;
	G_OBJECT_CLASS (klass)->finalize = omap_image_control_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), OMAP_IMAGE_CONTROL_LOCATION, g_param_spec_string ("location", "location", "location", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_WRITABLE));
}


static void omap_image_control_instance_init (OmapImageControl * self) {
}


static void omap_image_control_finalize (GObject* obj) {
	OmapImageControl * self;
	self = OMAP_IMAGE_CONTROL (obj);
	_gst_object_unref0 (self->filesrc);
	G_OBJECT_CLASS (omap_image_control_parent_class)->finalize (obj);
}


GType omap_image_control_get_type (void) {
	static volatile gsize omap_image_control_type_id__volatile = 0;
	if (g_once_init_enter (&omap_image_control_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (OmapImageControlClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) omap_image_control_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (OmapImageControl), 0, (GInstanceInitFunc) omap_image_control_instance_init, NULL };
		GType omap_image_control_type_id;
		omap_image_control_type_id = g_type_register_static (OMAP_TYPE_MEDIA_CONTROL, "OmapImageControl", &g_define_type_info, 0);
		g_once_init_leave (&omap_image_control_type_id__volatile, omap_image_control_type_id);
	}
	return omap_image_control_type_id__volatile;
}


static void omap_image_control_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	OmapImageControl * self;
	self = OMAP_IMAGE_CONTROL (object);
	switch (property_id) {
		case OMAP_IMAGE_CONTROL_LOCATION:
		omap_image_control_set_location (self, g_value_get_string (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}




