/* media-control.c generated by valac, the Vala compiler
 * generated from media-control.gs, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <gst/interfaces/xoverlay.h>
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
#define _gst_tag_list_free0(var) ((var == NULL) ? NULL : (var = (gst_tag_list_free (var), NULL)))
#define _gst_event_unref0(var) ((var == NULL) ? NULL : (var = (gst_event_unref (var), NULL)))

struct _MediaControl {
	GObject parent_instance;
	MediaControlPrivate * priv;
	GstXOverlay* xoverlay;
};

struct _MediaControlClass {
	GObjectClass parent_class;
};

struct _MediaControlPrivate {
	GstBin* _pipeline;
};


extern GQuark media_control_prepare_xwindow_q;
GQuark media_control_prepare_xwindow_q = 0U;
static gpointer media_control_parent_class = NULL;

GType media_control_get_type (void);
#define MEDIA_CONTROL_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_MEDIA_CONTROL, MediaControlPrivate))
enum  {
	MEDIA_CONTROL_DUMMY_PROPERTY,
	MEDIA_CONTROL_PIPELINE,
	MEDIA_CONTROL_STATE,
	MEDIA_CONTROL_POSITION,
	MEDIA_CONTROL_DURATION
};
void media_control_on_bus_message (MediaControl* self, GstMessage* message);
static void _media_control_on_bus_message_gst_bus_message (GstBus* _sender, GstMessage* message, gpointer self);
void media_control_on_bus_sync_message (MediaControl* self, GstMessage* message);
static void _media_control_on_bus_sync_message_gst_bus_message (GstBus* _sender, GstMessage* message, gpointer self);
void media_control_remove_signals (MediaControl* self);
static void _media_control_on_bus_sync_message_gst_bus_sync_message (GstBus* _sender, GstMessage* message, gpointer self);
void media_control_add_signals (MediaControl* self);
MediaControl* media_control_new (void);
MediaControl* media_control_construct (GType object_type);
GstBin* media_control_get_pipeline (MediaControl* self);
void media_control_set_pipeline (MediaControl* self, GstBin* value);
GstState media_control_get_state (MediaControl* self);
void media_control_set_state (MediaControl* self, GstState value);
gint64 media_control_get_position (MediaControl* self);
void media_control_set_position (MediaControl* self, gint64 value);
gint64 media_control_get_duration (MediaControl* self);
static void media_control_finalize (GObject* obj);
static void media_control_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void media_control_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);


static void g_cclosure_user_marshal_VOID__OBJECT_POINTER_STRING (GClosure * closure, GValue * return_value, guint n_param_values, const GValue * param_values, gpointer invocation_hint, gpointer marshal_data);
static void g_cclosure_user_marshal_VOID__OBJECT_POINTER (GClosure * closure, GValue * return_value, guint n_param_values, const GValue * param_values, gpointer invocation_hint, gpointer marshal_data);
static void g_cclosure_user_marshal_VOID__OBJECT_ENUM_INT64 (GClosure * closure, GValue * return_value, guint n_param_values, const GValue * param_values, gpointer invocation_hint, gpointer marshal_data);
static void g_cclosure_user_marshal_VOID__OBJECT_ENUM_ENUM_ENUM (GClosure * closure, GValue * return_value, guint n_param_values, const GValue * param_values, gpointer invocation_hint, gpointer marshal_data);

static gpointer _gst_object_ref0 (gpointer self) {
	return self ? gst_object_ref (self) : NULL;
}


static void _media_control_on_bus_message_gst_bus_message (GstBus* _sender, GstMessage* message, gpointer self) {
	media_control_on_bus_message (self, message);
}


static void _media_control_on_bus_sync_message_gst_bus_message (GstBus* _sender, GstMessage* message, gpointer self) {
	media_control_on_bus_sync_message (self, message);
}


void media_control_remove_signals (MediaControl* self) {
	GstBus* bus;
	guint _tmp0_;
	guint _tmp1_;
	g_return_if_fail (self != NULL);
	bus = _gst_object_ref0 (((GstElement*) self->priv->_pipeline)->bus);
	g_signal_handlers_disconnect_matched (bus, G_SIGNAL_MATCH_ID | G_SIGNAL_MATCH_FUNC | G_SIGNAL_MATCH_DATA, (g_signal_parse_name ("message", GST_TYPE_BUS, &_tmp0_, NULL, FALSE), _tmp0_), 0, NULL, (GCallback) _media_control_on_bus_message_gst_bus_message, self);
	g_signal_handlers_disconnect_matched (bus, G_SIGNAL_MATCH_ID | G_SIGNAL_MATCH_FUNC | G_SIGNAL_MATCH_DATA, (g_signal_parse_name ("message", GST_TYPE_BUS, &_tmp1_, NULL, FALSE), _tmp1_), 0, NULL, (GCallback) _media_control_on_bus_sync_message_gst_bus_message, self);
	_gst_object_unref0 (bus);
}


static void _media_control_on_bus_sync_message_gst_bus_sync_message (GstBus* _sender, GstMessage* message, gpointer self) {
	media_control_on_bus_sync_message (self, message);
}


void media_control_add_signals (MediaControl* self) {
	GstBus* bus;
	g_return_if_fail (self != NULL);
	bus = _gst_object_ref0 (((GstElement*) self->priv->_pipeline)->bus);
	gst_bus_add_signal_watch (bus);
	gst_bus_enable_sync_message_emission (bus);
	g_signal_connect_object (bus, "message", (GCallback) _media_control_on_bus_message_gst_bus_message, self, 0);
	g_signal_connect_object (bus, "sync-message", (GCallback) _media_control_on_bus_sync_message_gst_bus_sync_message, self, 0);
	_gst_object_unref0 (bus);
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
					g_signal_emit_by_name (self, "element-message", message->src, st);
				}
				_gst_structure_free0 (st);
			}
			break;
		}
		case GST_MESSAGE_EOS:
		{
			{
				g_signal_emit_by_name (self, "eos-message", message->src);
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
				g_signal_emit_by_name (self, "error-message", message->src, e, d);
				_g_error_free0 (e);
				_g_free0 (d);
			}
			break;
		}
		case GST_MESSAGE_STATE_CHANGED:
		{
			{
				GstState old = 0;
				GstState current = 0;
				GstState pending = 0;
				gst_message_parse_state_changed (message, &old, &current, &pending);
				g_signal_emit_by_name (self, "state-changed-message", message->src, old, current, pending);
			}
			break;
		}
		case GST_MESSAGE_SEGMENT_START:
		{
			{
				GstFormat format = 0;
				gint64 position = 0LL;
				gst_message_parse_segment_start (message, &format, &position);
				g_signal_emit_by_name (self, "segment-start-message", message->src, format, position);
			}
			break;
		}
		case GST_MESSAGE_SEGMENT_DONE:
		{
			{
				GstFormat format = 0;
				gint64 position = 0LL;
				gst_message_parse_segment_done (message, &format, &position);
				g_signal_emit_by_name (self, "segment-done-message", message->src, format, position);
			}
			break;
		}
		case GST_MESSAGE_TAG:
		{
			{
				GstTagList* tag_list;
				GstTagList* _tmp6_;
				GstTagList* _tmp5_ = NULL;
				tag_list = NULL;
				gst_message_parse_tag (message, &_tmp5_);
				tag_list = (_tmp6_ = _tmp5_, _gst_tag_list_free0 (tag_list), _tmp6_);
				g_signal_emit_by_name (self, "tag-message", message->src, tag_list);
				_gst_tag_list_free0 (tag_list);
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


void media_control_on_bus_sync_message (MediaControl* self, GstMessage* message) {
	GstStructure* structure;
	GstStructure* _tmp0_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (message != NULL);
	structure = NULL;
	if ((structure = (_tmp0_ = _gst_structure_copy0 (message->structure), _gst_structure_free0 (structure), _tmp0_)) == NULL) {
		_gst_structure_free0 (structure);
		return;
	}
	if (structure->name == media_control_prepare_xwindow_q) {
		GstXOverlay* _tmp2_;
		GstObject* _tmp1_;
		self->xoverlay = (_tmp2_ = _gst_object_ref0 ((_tmp1_ = message->src, GST_IS_X_OVERLAY (_tmp1_) ? ((GstXOverlay*) _tmp1_) : NULL)), _gst_object_unref0 (self->xoverlay), _tmp2_);
		g_signal_emit_by_name (self, "prepare-xwindow-id", self->xoverlay);
	}
	_gst_structure_free0 (structure);
}


MediaControl* media_control_construct (GType object_type) {
	MediaControl * self;
	self = (MediaControl*) g_object_new (object_type, NULL);
	return self;
}


MediaControl* media_control_new (void) {
	return media_control_construct (TYPE_MEDIA_CONTROL);
}


GstBin* media_control_get_pipeline (MediaControl* self) {
	GstBin* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_pipeline;
	return result;
}


void media_control_set_pipeline (MediaControl* self, GstBin* value) {
	GstBin* _tmp0_;
	g_return_if_fail (self != NULL);
	if (self->priv->_pipeline != NULL) {
		media_control_remove_signals (self);
	}
	self->priv->_pipeline = (_tmp0_ = _gst_object_ref0 (value), _gst_object_unref0 (self->priv->_pipeline), _tmp0_);
	media_control_add_signals (self);
	g_object_notify ((GObject *) self, "pipeline");
}


GstState media_control_get_state (MediaControl* self) {
	GstState result;
	GstState state = 0;
	g_return_val_if_fail (self != NULL, 0);
	gst_element_get_state ((GstElement*) media_control_get_pipeline (self), &state, NULL, (GstClockTime) (GST_MSECOND * 50));
	result = state;
	return result;
}


void media_control_set_state (MediaControl* self, GstState value) {
	g_return_if_fail (self != NULL);
	gst_element_set_state ((GstElement*) media_control_get_pipeline (self), value);
	g_object_notify ((GObject *) self, "state");
}


gint64 media_control_get_position (MediaControl* self) {
	gint64 result;
	GstFormat format;
	gint64 position = 0LL;
	g_return_val_if_fail (self != NULL, 0LL);
	format = GST_FORMAT_TIME;
	gst_element_query_position ((GstElement*) media_control_get_pipeline (self), &format, &position);
	result = position;
	return result;
}


static gpointer _gst_event_ref0 (gpointer self) {
	return self ? gst_event_ref (self) : NULL;
}


void media_control_set_position (MediaControl* self, gint64 value) {
	GstEvent* seek_event;
	g_return_if_fail (self != NULL);
	seek_event = gst_event_new_seek (1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_ACCURATE, GST_SEEK_TYPE_SET, value, GST_SEEK_TYPE_NONE, (gint64) 0);
	gst_element_send_event ((GstElement*) media_control_get_pipeline (self), _gst_event_ref0 (seek_event));
	_gst_event_unref0 (seek_event);
	g_object_notify ((GObject *) self, "position");
}


gint64 media_control_get_duration (MediaControl* self) {
	gint64 result;
	GstFormat format;
	gint64 duration = 0LL;
	g_return_val_if_fail (self != NULL, 0LL);
	format = GST_FORMAT_TIME;
	gst_element_query_duration ((GstElement*) media_control_get_pipeline (self), &format, &duration);
	result = duration;
	return result;
}


static void media_control_class_init (MediaControlClass * klass) {
	media_control_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (MediaControlPrivate));
	G_OBJECT_CLASS (klass)->get_property = media_control_get_property;
	G_OBJECT_CLASS (klass)->set_property = media_control_set_property;
	G_OBJECT_CLASS (klass)->finalize = media_control_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), MEDIA_CONTROL_PIPELINE, g_param_spec_object ("pipeline", "pipeline", "pipeline", GST_TYPE_BIN, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), MEDIA_CONTROL_STATE, g_param_spec_enum ("state", "state", "state", GST_TYPE_STATE, 0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), MEDIA_CONTROL_POSITION, g_param_spec_int64 ("position", "position", "position", G_MININT64, G_MAXINT64, 0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), MEDIA_CONTROL_DURATION, g_param_spec_int64 ("duration", "duration", "duration", G_MININT64, G_MAXINT64, 0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE));
	g_signal_new ("prepare_xwindow_id", TYPE_MEDIA_CONTROL, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__OBJECT, G_TYPE_NONE, 1, GST_TYPE_X_OVERLAY);
	g_signal_new ("eos_message", TYPE_MEDIA_CONTROL, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__OBJECT, G_TYPE_NONE, 1, GST_TYPE_OBJECT);
	g_signal_new ("error_message", TYPE_MEDIA_CONTROL, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_user_marshal_VOID__OBJECT_POINTER_STRING, G_TYPE_NONE, 3, GST_TYPE_OBJECT, G_TYPE_POINTER, G_TYPE_STRING);
	g_signal_new ("element_message", TYPE_MEDIA_CONTROL, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_user_marshal_VOID__OBJECT_POINTER, G_TYPE_NONE, 2, GST_TYPE_OBJECT, G_TYPE_POINTER);
	g_signal_new ("segment_start_message", TYPE_MEDIA_CONTROL, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_user_marshal_VOID__OBJECT_ENUM_INT64, G_TYPE_NONE, 3, GST_TYPE_OBJECT, GST_TYPE_FORMAT, G_TYPE_INT64);
	g_signal_new ("segment_done_message", TYPE_MEDIA_CONTROL, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_user_marshal_VOID__OBJECT_ENUM_INT64, G_TYPE_NONE, 3, GST_TYPE_OBJECT, GST_TYPE_FORMAT, G_TYPE_INT64);
	g_signal_new ("tag_message", TYPE_MEDIA_CONTROL, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_user_marshal_VOID__OBJECT_POINTER, G_TYPE_NONE, 2, GST_TYPE_OBJECT, G_TYPE_POINTER);
	g_signal_new ("state_changed_message", TYPE_MEDIA_CONTROL, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_user_marshal_VOID__OBJECT_ENUM_ENUM_ENUM, G_TYPE_NONE, 4, GST_TYPE_OBJECT, GST_TYPE_STATE, GST_TYPE_STATE, GST_TYPE_STATE);
	media_control_prepare_xwindow_q = g_quark_from_string ("prepare-xwindow-id");
}


static void media_control_instance_init (MediaControl * self) {
	self->priv = MEDIA_CONTROL_GET_PRIVATE (self);
}


static void media_control_finalize (GObject* obj) {
	MediaControl * self;
	self = MEDIA_CONTROL (obj);
	{
		if (self->priv->_pipeline != NULL) {
			media_control_remove_signals (self);
		}
	}
	_gst_object_unref0 (self->priv->_pipeline);
	_gst_object_unref0 (self->xoverlay);
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


static void media_control_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	MediaControl * self;
	self = MEDIA_CONTROL (object);
	switch (property_id) {
		case MEDIA_CONTROL_PIPELINE:
		g_value_set_object (value, media_control_get_pipeline (self));
		break;
		case MEDIA_CONTROL_STATE:
		g_value_set_enum (value, media_control_get_state (self));
		break;
		case MEDIA_CONTROL_POSITION:
		g_value_set_int64 (value, media_control_get_position (self));
		break;
		case MEDIA_CONTROL_DURATION:
		g_value_set_int64 (value, media_control_get_duration (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void media_control_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	MediaControl * self;
	self = MEDIA_CONTROL (object);
	switch (property_id) {
		case MEDIA_CONTROL_PIPELINE:
		media_control_set_pipeline (self, g_value_get_object (value));
		break;
		case MEDIA_CONTROL_STATE:
		media_control_set_state (self, g_value_get_enum (value));
		break;
		case MEDIA_CONTROL_POSITION:
		media_control_set_position (self, g_value_get_int64 (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}



static void g_cclosure_user_marshal_VOID__OBJECT_POINTER_STRING (GClosure * closure, GValue * return_value, guint n_param_values, const GValue * param_values, gpointer invocation_hint, gpointer marshal_data) {
	typedef void (*GMarshalFunc_VOID__OBJECT_POINTER_STRING) (gpointer data1, gpointer arg_1, gpointer arg_2, const char* arg_3, gpointer data2);
	register GMarshalFunc_VOID__OBJECT_POINTER_STRING callback;
	register GCClosure * cc;
	register gpointer data1, data2;
	cc = (GCClosure *) closure;
	g_return_if_fail (n_param_values == 4);
	if (G_CCLOSURE_SWAP_DATA (closure)) {
		data1 = closure->data;
		data2 = param_values->data[0].v_pointer;
	} else {
		data1 = param_values->data[0].v_pointer;
		data2 = closure->data;
	}
	callback = (GMarshalFunc_VOID__OBJECT_POINTER_STRING) (marshal_data ? marshal_data : cc->callback);
	callback (data1, g_value_get_object (param_values + 1), g_value_get_pointer (param_values + 2), g_value_get_string (param_values + 3), data2);
}


static void g_cclosure_user_marshal_VOID__OBJECT_POINTER (GClosure * closure, GValue * return_value, guint n_param_values, const GValue * param_values, gpointer invocation_hint, gpointer marshal_data) {
	typedef void (*GMarshalFunc_VOID__OBJECT_POINTER) (gpointer data1, gpointer arg_1, gpointer arg_2, gpointer data2);
	register GMarshalFunc_VOID__OBJECT_POINTER callback;
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
	callback = (GMarshalFunc_VOID__OBJECT_POINTER) (marshal_data ? marshal_data : cc->callback);
	callback (data1, g_value_get_object (param_values + 1), g_value_get_pointer (param_values + 2), data2);
}


static void g_cclosure_user_marshal_VOID__OBJECT_ENUM_INT64 (GClosure * closure, GValue * return_value, guint n_param_values, const GValue * param_values, gpointer invocation_hint, gpointer marshal_data) {
	typedef void (*GMarshalFunc_VOID__OBJECT_ENUM_INT64) (gpointer data1, gpointer arg_1, gint arg_2, gint64 arg_3, gpointer data2);
	register GMarshalFunc_VOID__OBJECT_ENUM_INT64 callback;
	register GCClosure * cc;
	register gpointer data1, data2;
	cc = (GCClosure *) closure;
	g_return_if_fail (n_param_values == 4);
	if (G_CCLOSURE_SWAP_DATA (closure)) {
		data1 = closure->data;
		data2 = param_values->data[0].v_pointer;
	} else {
		data1 = param_values->data[0].v_pointer;
		data2 = closure->data;
	}
	callback = (GMarshalFunc_VOID__OBJECT_ENUM_INT64) (marshal_data ? marshal_data : cc->callback);
	callback (data1, g_value_get_object (param_values + 1), g_value_get_enum (param_values + 2), g_value_get_int64 (param_values + 3), data2);
}


static void g_cclosure_user_marshal_VOID__OBJECT_ENUM_ENUM_ENUM (GClosure * closure, GValue * return_value, guint n_param_values, const GValue * param_values, gpointer invocation_hint, gpointer marshal_data) {
	typedef void (*GMarshalFunc_VOID__OBJECT_ENUM_ENUM_ENUM) (gpointer data1, gpointer arg_1, gint arg_2, gint arg_3, gint arg_4, gpointer data2);
	register GMarshalFunc_VOID__OBJECT_ENUM_ENUM_ENUM callback;
	register GCClosure * cc;
	register gpointer data1, data2;
	cc = (GCClosure *) closure;
	g_return_if_fail (n_param_values == 5);
	if (G_CCLOSURE_SWAP_DATA (closure)) {
		data1 = closure->data;
		data2 = param_values->data[0].v_pointer;
	} else {
		data1 = param_values->data[0].v_pointer;
		data2 = closure->data;
	}
	callback = (GMarshalFunc_VOID__OBJECT_ENUM_ENUM_ENUM) (marshal_data ? marshal_data : cc->callback);
	callback (data1, g_value_get_object (param_values + 1), g_value_get_enum (param_values + 2), g_value_get_enum (param_values + 3), g_value_get_enum (param_values + 4), data2);
}



