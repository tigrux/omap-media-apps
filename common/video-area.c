/* video-area.c generated by valac, the Vala compiler
 * generated from video-area.gs, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <gst/gst.h>
#include <gst/interfaces/xoverlay.h>
#include <gdk/gdk.h>
#include <gdk/gdkx.h>


#define TYPE_VIDEO_AREA (video_area_get_type ())
#define VIDEO_AREA(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_VIDEO_AREA, VideoArea))
#define VIDEO_AREA_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_VIDEO_AREA, VideoAreaClass))
#define IS_VIDEO_AREA(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_VIDEO_AREA))
#define IS_VIDEO_AREA_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_VIDEO_AREA))
#define VIDEO_AREA_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_VIDEO_AREA, VideoAreaClass))

typedef struct _VideoArea VideoArea;
typedef struct _VideoAreaClass VideoAreaClass;
typedef struct _VideoAreaPrivate VideoAreaPrivate;
#define _gst_object_unref0(var) ((var == NULL) ? NULL : (var = (gst_object_unref (var), NULL)))

#define TYPE_MEDIA_CONTROL (media_control_get_type ())
#define MEDIA_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_MEDIA_CONTROL, MediaControl))
#define MEDIA_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_MEDIA_CONTROL, MediaControlClass))
#define IS_MEDIA_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_MEDIA_CONTROL))
#define IS_MEDIA_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_MEDIA_CONTROL))
#define MEDIA_CONTROL_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_MEDIA_CONTROL, MediaControlClass))

typedef struct _MediaControl MediaControl;
typedef struct _MediaControlClass MediaControlClass;
#define _gst_structure_free0(var) ((var == NULL) ? NULL : (var = (gst_structure_free (var), NULL)))

struct _VideoArea {
	GtkDrawingArea parent_instance;
	VideoAreaPrivate * priv;
	guint32 xid;
	GstBus* bus;
	GstXOverlay* imagesink;
};

struct _VideoAreaClass {
	GtkDrawingAreaClass parent_class;
};


extern GQuark video_area_prepare_xwindow_q;
GQuark video_area_prepare_xwindow_q = 0U;
static gpointer video_area_parent_class = NULL;

GType video_area_get_type (void);
enum  {
	VIDEO_AREA_DUMMY_PROPERTY
};
static inline void _dynamic_set_force_aspect_ratio0 (GstXOverlay* obj, gboolean value);
void video_area_set_sink (VideoArea* self, GstXOverlay* sink);
static gboolean video_area_real_button_press_event (GtkWidget* base, GdkEventButton* event);
static gboolean video_area_real_expose_event (GtkWidget* base, GdkEventExpose* event);
GType media_control_get_type (void);
GstBus* media_control_get_bus (MediaControl* self);
void video_area_on_bus_sync_message (VideoArea* self, GstMessage* message);
static void _video_area_on_bus_sync_message_gst_bus_sync_message (GstBus* _sender, GstMessage* message, gpointer self);
void video_area_set_control (VideoArea* self, MediaControl* control);
VideoArea* video_area_new (void);
VideoArea* video_area_construct (GType object_type);
static void _lambda0_ (VideoArea* self);
static void __lambda0__gtk_widget_realize (VideoArea* _sender, gpointer self);
static GObject * video_area_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static void video_area_finalize (GObject* obj);



static gpointer _gst_object_ref0 (gpointer self) {
	return self ? gst_object_ref (self) : NULL;
}


static inline void _dynamic_set_force_aspect_ratio0 (GstXOverlay* obj, gboolean value) {
	g_object_set (obj, "force-aspect-ratio", value, NULL);
}


void video_area_set_sink (VideoArea* self, GstXOverlay* sink) {
	GstXOverlay* _tmp0_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (sink != NULL);
	self->imagesink = (_tmp0_ = _gst_object_ref0 (sink), _gst_object_unref0 (self->imagesink), _tmp0_);
	_dynamic_set_force_aspect_ratio0 (self->imagesink, TRUE);
	gst_x_overlay_set_xwindow_id (self->imagesink, (gulong) self->xid);
}


static gboolean video_area_real_button_press_event (GtkWidget* base, GdkEventButton* event) {
	VideoArea * self;
	gboolean result;
	self = (VideoArea*) base;
	if ((*event).type == GDK_2BUTTON_PRESS) {
		g_signal_emit_by_name (self, "activated");
	}
	result = TRUE;
	return result;
}


static gboolean video_area_real_expose_event (GtkWidget* base, GdkEventExpose* event) {
	VideoArea * self;
	gboolean result;
	self = (VideoArea*) base;
	if (self->imagesink != NULL) {
		gst_x_overlay_expose (self->imagesink);
		result = FALSE;
		return result;
	}
	result = TRUE;
	return result;
}


static void _video_area_on_bus_sync_message_gst_bus_sync_message (GstBus* _sender, GstMessage* message, gpointer self) {
	video_area_on_bus_sync_message (self, message);
}


void video_area_set_control (VideoArea* self, MediaControl* control) {
	GstBus* _tmp0_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (control != NULL);
	self->bus = (_tmp0_ = media_control_get_bus (control), _gst_object_unref0 (self->bus), _tmp0_);
	gst_bus_enable_sync_message_emission (self->bus);
	g_signal_connect_object (self->bus, "sync-message", (GCallback) _video_area_on_bus_sync_message_gst_bus_sync_message, self, 0);
}


static gpointer _gst_structure_copy0 (gpointer self) {
	return self ? gst_structure_copy (self) : NULL;
}


void video_area_on_bus_sync_message (VideoArea* self, GstMessage* message) {
	GstStructure* structure;
	GstStructure* _tmp0_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (message != NULL);
	structure = NULL;
	if ((structure = (_tmp0_ = _gst_structure_copy0 (message->structure), _gst_structure_free0 (structure), _tmp0_)) == NULL) {
		_gst_structure_free0 (structure);
		return;
	}
	if (structure->name == video_area_prepare_xwindow_q) {
		GstObject* _tmp1_;
		GstXOverlay* imagesink;
		imagesink = _gst_object_ref0 ((_tmp1_ = message->src, GST_IS_X_OVERLAY (_tmp1_) ? ((GstXOverlay*) _tmp1_) : NULL));
		video_area_set_sink (self, imagesink);
		g_signal_emit_by_name (self, "prepared");
		_gst_object_unref0 (imagesink);
	}
	_gst_structure_free0 (structure);
}


VideoArea* video_area_construct (GType object_type) {
	VideoArea * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


VideoArea* video_area_new (void) {
	return video_area_construct (TYPE_VIDEO_AREA);
}


static void _lambda0_ (VideoArea* self) {
	self->xid = gdk_x11_drawable_get_xid ((GdkDrawable*) ((GtkWidget*) self)->window);
}


static void __lambda0__gtk_widget_realize (VideoArea* _sender, gpointer self) {
	_lambda0_ (self);
}


static GObject * video_area_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GObjectClass * parent_class;
	VideoArea * self;
	parent_class = G_OBJECT_CLASS (video_area_parent_class);
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = VIDEO_AREA (obj);
	{
		gtk_widget_set_double_buffered ((GtkWidget*) self, FALSE);
		gtk_widget_add_events ((GtkWidget*) self, (gint) GDK_BUTTON_PRESS_MASK);
		gtk_widget_add_events ((GtkWidget*) self, (gint) GDK_BUTTON_RELEASE_MASK);
		g_signal_connect_object ((GtkWidget*) self, "realize", (GCallback) __lambda0__gtk_widget_realize, self, 0);
	}
	return obj;
}


static void video_area_class_init (VideoAreaClass * klass) {
	video_area_parent_class = g_type_class_peek_parent (klass);
	GTK_WIDGET_CLASS (klass)->button_press_event = video_area_real_button_press_event;
	GTK_WIDGET_CLASS (klass)->expose_event = video_area_real_expose_event;
	G_OBJECT_CLASS (klass)->constructor = video_area_constructor;
	G_OBJECT_CLASS (klass)->finalize = video_area_finalize;
	g_signal_new ("prepared", TYPE_VIDEO_AREA, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);
	g_signal_new ("activated", TYPE_VIDEO_AREA, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);
	video_area_prepare_xwindow_q = g_quark_from_string ("prepare-xwindow-id");
}


static void video_area_instance_init (VideoArea * self) {
}


static void video_area_finalize (GObject* obj) {
	VideoArea * self;
	self = VIDEO_AREA (obj);
	{
		if (self->bus != NULL) {
			guint _tmp0_;
			g_signal_handlers_disconnect_matched (self->bus, G_SIGNAL_MATCH_ID | G_SIGNAL_MATCH_FUNC | G_SIGNAL_MATCH_DATA, (g_signal_parse_name ("sync-message", GST_TYPE_BUS, &_tmp0_, NULL, FALSE), _tmp0_), 0, NULL, (GCallback) _video_area_on_bus_sync_message_gst_bus_sync_message, self);
		}
	}
	_gst_object_unref0 (self->bus);
	_gst_object_unref0 (self->imagesink);
	G_OBJECT_CLASS (video_area_parent_class)->finalize (obj);
}


GType video_area_get_type (void) {
	static GType video_area_type_id = 0;
	if (video_area_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (VideoAreaClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) video_area_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (VideoArea), 0, (GInstanceInitFunc) video_area_instance_init, NULL };
		video_area_type_id = g_type_register_static (GTK_TYPE_DRAWING_AREA, "VideoArea", &g_define_type_info, 0);
	}
	return video_area_type_id;
}




