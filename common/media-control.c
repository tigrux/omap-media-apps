/* media-control.c generated by valac, the Vala compiler
 * generated from media-control.gs, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <gst/gst.h>
#include <stdlib.h>
#include <string.h>


#define TYPE_MEDIA_CONTROL (media_control_get_type ())
#define MEDIA_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_MEDIA_CONTROL, MediaControl))
#define MEDIA_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_MEDIA_CONTROL, MediaControlClass))
#define IS_MEDIA_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_MEDIA_CONTROL))
#define IS_MEDIA_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_MEDIA_CONTROL))
#define MEDIA_CONTROL_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_MEDIA_CONTROL, MediaControlClass))

typedef struct _MediaControl MediaControl;
typedef struct _MediaControlClass MediaControlClass;
typedef struct _MediaControlPrivate MediaControlPrivate;
#define _gst_object_unref0(var) ((var == NULL) ? NULL : (var = (gst_object_unref (var), NULL)))
#define _gst_structure_free0(var) ((var == NULL) ? NULL : (var = (gst_structure_free (var), NULL)))
#define _g_error_free0(var) ((var == NULL) ? NULL : (var = (g_error_free (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))
#define _gst_event_unref0(var) ((var == NULL) ? NULL : (var = (gst_event_unref (var), NULL)))

struct _MediaControl {
	GObject parent_instance;
	MediaControlPrivate * priv;
	GstBus* bus;
	GstBin* pipeline;
};

struct _MediaControlClass {
	GObjectClass parent_class;
};


static gpointer media_control_parent_class = NULL;

GType media_control_get_type (void);
enum  {
	MEDIA_CONTROL_DUMMY_PROPERTY
};
void media_control_on_bus_message (MediaControl* self, GstMessage* message);
static void _media_control_on_bus_message_gst_bus_message (GstBus* _sender, GstMessage* message, gpointer self);
void media_control_set_pipeline (MediaControl* self, GstBin* bin);
GstBus* media_control_get_bus (MediaControl* self);
void media_control_seek (MediaControl* self, gint64 location);
GstState media_control_get_state (MediaControl* self);
GstStateChangeReturn media_control_set_state (MediaControl* self, GstState state);
gint64 media_control_get_position (MediaControl* self);
gint64 media_control_get_duration (MediaControl* self);
MediaControl* media_control_new (void);
MediaControl* media_control_construct (GType object_type);
static void media_control_finalize (GObject* obj);


static void g_cclosure_user_marshal_VOID__POINTER_STRING (GClosure * closure, GValue * return_value, guint n_param_values, const GValue * param_values, gpointer invocation_hint, gpointer marshal_data);
static void g_cclosure_user_marshal_VOID__OBJECT_STRING (GClosure * closure, GValue * return_value, guint n_param_values, const GValue * param_values, gpointer invocation_hint, gpointer marshal_data);

static void _media_control_on_bus_message_gst_bus_message (GstBus* _sender, GstMessage* message, gpointer self) {
	media_control_on_bus_message (self, message);
}


static gpointer _gst_object_ref0 (gpointer self) {
	return self ? gst_object_ref (self) : NULL;
}


void media_control_set_pipeline (MediaControl* self, GstBin* bin) {
	GstBin* _tmp1_;
	GstBus* _tmp2_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (bin != NULL);
	if (self->bus != NULL) {
		guint _tmp0_;
		g_signal_handlers_disconnect_matched (self->bus, G_SIGNAL_MATCH_ID | G_SIGNAL_MATCH_FUNC | G_SIGNAL_MATCH_DATA, (g_signal_parse_name ("message", GST_TYPE_BUS, &_tmp0_, NULL, FALSE), _tmp0_), 0, NULL, (GCallback) _media_control_on_bus_message_gst_bus_message, self);
	}
	self->pipeline = (_tmp1_ = _gst_object_ref0 (bin), _gst_object_unref0 (self->pipeline), _tmp1_);
	self->bus = (_tmp2_ = gst_element_get_bus ((GstElement*) self->pipeline), _gst_object_unref0 (self->bus), _tmp2_);
	gst_bus_add_signal_watch (self->bus);
	g_signal_connect_object (self->bus, "message", (GCallback) _media_control_on_bus_message_gst_bus_message, self, 0);
}


GstBus* media_control_get_bus (MediaControl* self) {
	GstBus* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = _gst_object_ref0 (self->bus);
	return result;
}


static gpointer _gst_structure_copy0 (gpointer self) {
	return self ? gst_structure_copy (self) : NULL;
}


void media_control_on_bus_message (MediaControl* self, GstMessage* message) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (message != NULL);
	switch (message->type) {
		case GST_MESSAGE_ELEMENT:
		{
			{
				GstStructure* st;
				GstStructure* _tmp0_;
				st = NULL;
				if ((st = (_tmp0_ = _gst_structure_copy0 (message->structure), _gst_structure_free0 (st), _tmp0_)) != NULL) {
					g_signal_emit_by_name (self, "structure-message", message->src, gst_structure_get_name (st));
				}
				_gst_structure_free0 (st);
			}
			break;
		}
		case GST_MESSAGE_EOS:
		{
			{
				g_signal_emit_by_name (self, "eos-message");
			}
			break;
		}
		case GST_MESSAGE_ERROR:
		{
			{
				GError* e;
				char* d;
				char* _tmp4_;
				char* _tmp3_ = NULL;
				GError* _tmp2_;
				GError* _tmp1_ = NULL;
				e = NULL;
				d = NULL;
				(gst_message_parse_error (message, &_tmp1_, &_tmp3_), e = (_tmp2_ = _tmp1_, _g_error_free0 (e), _tmp2_));
				d = (_tmp4_ = _tmp3_, _g_free0 (d), _tmp4_);
				g_signal_emit_by_name (self, "error-message", e, d);
				_g_error_free0 (e);
				_g_free0 (d);
			}
			break;
		}
		default:
		{
			{
				;
			}
			break;
		}
	}
}


static gpointer _gst_event_ref0 (gpointer self) {
	return self ? gst_event_ref (self) : NULL;
}


void media_control_seek (MediaControl* self, gint64 location) {
	GstEvent* seek_event;
	g_return_if_fail (self != NULL);
	seek_event = gst_event_new_seek (1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_ACCURATE, GST_SEEK_TYPE_SET, location, GST_SEEK_TYPE_NONE, (gint64) 0);
	gst_element_send_event ((GstElement*) self->pipeline, _gst_event_ref0 (seek_event));
	_gst_event_unref0 (seek_event);
}


GstState media_control_get_state (MediaControl* self) {
	GstState result;
	GstState state = 0;
	g_return_val_if_fail (self != NULL, 0);
	gst_element_get_state ((GstElement*) self->pipeline, &state, NULL, (GstClockTime) (GST_MSECOND * 50));
	result = state;
	return result;
}


GstStateChangeReturn media_control_set_state (MediaControl* self, GstState state) {
	GstStateChangeReturn result;
	g_return_val_if_fail (self != NULL, 0);
	result = gst_element_set_state ((GstElement*) self->pipeline, state);
	return result;
}


gint64 media_control_get_position (MediaControl* self) {
	gint64 result;
	GstFormat format;
	gint64 position = 0LL;
	g_return_val_if_fail (self != NULL, 0LL);
	format = GST_FORMAT_TIME;
	gst_element_query_position ((GstElement*) self->pipeline, &format, &position);
	result = position;
	return result;
}


gint64 media_control_get_duration (MediaControl* self) {
	gint64 result;
	GstFormat format;
	gint64 duration = 0LL;
	g_return_val_if_fail (self != NULL, 0LL);
	format = GST_FORMAT_TIME;
	gst_element_query_duration ((GstElement*) self->pipeline, &format, &duration);
	result = duration;
	return result;
}


MediaControl* media_control_construct (GType object_type) {
	MediaControl * self;
	self = (MediaControl*) g_object_new (object_type, NULL);
	return self;
}


MediaControl* media_control_new (void) {
	return media_control_construct (TYPE_MEDIA_CONTROL);
}


static void media_control_class_init (MediaControlClass * klass) {
	media_control_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->finalize = media_control_finalize;
	g_signal_new ("eos_message", TYPE_MEDIA_CONTROL, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);
	g_signal_new ("error_message", TYPE_MEDIA_CONTROL, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_user_marshal_VOID__POINTER_STRING, G_TYPE_NONE, 2, G_TYPE_POINTER, G_TYPE_STRING);
	g_signal_new ("structure_message", TYPE_MEDIA_CONTROL, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_user_marshal_VOID__OBJECT_STRING, G_TYPE_NONE, 2, GST_TYPE_OBJECT, G_TYPE_STRING);
}


static void media_control_instance_init (MediaControl * self) {
}


static void media_control_finalize (GObject* obj) {
	MediaControl * self;
	self = MEDIA_CONTROL (obj);
	_gst_object_unref0 (self->bus);
	_gst_object_unref0 (self->pipeline);
	G_OBJECT_CLASS (media_control_parent_class)->finalize (obj);
}


GType media_control_get_type (void) {
	static GType media_control_type_id = 0;
	if (media_control_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (MediaControlClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) media_control_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (MediaControl), 0, (GInstanceInitFunc) media_control_instance_init, NULL };
		media_control_type_id = g_type_register_static (G_TYPE_OBJECT, "MediaControl", &g_define_type_info, 0);
	}
	return media_control_type_id;
}



static void g_cclosure_user_marshal_VOID__POINTER_STRING (GClosure * closure, GValue * return_value, guint n_param_values, const GValue * param_values, gpointer invocation_hint, gpointer marshal_data) {
	typedef void (*GMarshalFunc_VOID__POINTER_STRING) (gpointer data1, gpointer arg_1, const char* arg_2, gpointer data2);
	register GMarshalFunc_VOID__POINTER_STRING callback;
	register GCClosure * cc;
	register gpointer data1, data2;
	cc = (GCClosure *) closure;
	g_return_if_fail (n_param_values == 3);
	if (G_CCLOSURE_SWAP_DATA (closure)) {
		data1 = closure->data;
		data2 = param_values->data[0].v_pointer;
	} else {
		data1 = param_values->data[0].v_pointer;
		data2 = closure->data;
	}
	callback = (GMarshalFunc_VOID__POINTER_STRING) (marshal_data ? marshal_data : cc->callback);
	callback (data1, g_value_get_pointer (param_values + 1), g_value_get_string (param_values + 2), data2);
}


static void g_cclosure_user_marshal_VOID__OBJECT_STRING (GClosure * closure, GValue * return_value, guint n_param_values, const GValue * param_values, gpointer invocation_hint, gpointer marshal_data) {
	typedef void (*GMarshalFunc_VOID__OBJECT_STRING) (gpointer data1, gpointer arg_1, const char* arg_2, gpointer data2);
	register GMarshalFunc_VOID__OBJECT_STRING callback;
	register GCClosure * cc;
	register gpointer data1, data2;
	cc = (GCClosure *) closure;
	g_return_if_fail (n_param_values == 3);
	if (G_CCLOSURE_SWAP_DATA (closure)) {
		data1 = closure->data;
		data2 = param_values->data[0].v_pointer;
	} else {
		data1 = param_values->data[0].v_pointer;
		data2 = closure->data;
	}
	callback = (GMarshalFunc_VOID__OBJECT_STRING) (marshal_data ? marshal_data : cc->callback);
	callback (data1, g_value_get_object (param_values + 1), g_value_get_string (param_values + 2), data2);
}


