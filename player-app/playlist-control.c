/* playlist-control.c generated by valac, the Vala compiler
 * generated from playlist-control.gs, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <gst/gst.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>


#define TYPE_PLAY_LIST_CONTROL (play_list_control_get_type ())
#define PLAY_LIST_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_PLAY_LIST_CONTROL, PlayListControl))
#define PLAY_LIST_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_PLAY_LIST_CONTROL, PlayListControlClass))
#define IS_PLAY_LIST_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_PLAY_LIST_CONTROL))
#define IS_PLAY_LIST_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_PLAY_LIST_CONTROL))
#define PLAY_LIST_CONTROL_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_PLAY_LIST_CONTROL, PlayListControlClass))

typedef struct _PlayListControl PlayListControl;
typedef struct _PlayListControlClass PlayListControlClass;
typedef struct _PlayListControlPrivate PlayListControlPrivate;
#define _gst_object_unref0(var) ((var == NULL) ? NULL : (var = (gst_object_unref (var), NULL)))
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _gtk_tree_path_free0(var) ((var == NULL) ? NULL : (var = (gtk_tree_path_free (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))

#define TYPE_PLAY_LIST_COL (play_list_col_get_type ())
#define _gst_event_unref0(var) ((var == NULL) ? NULL : (var = (gst_event_unref (var), NULL)))

struct _PlayListControl {
	GObject parent_instance;
	PlayListControlPrivate * priv;
	GstElement* player;
	GtkListStore* playlist_store;
	GtkTreePath* current_row;
	gint number_of_rows;
};

struct _PlayListControlClass {
	GObjectClass parent_class;
};

typedef enum  {
	PLAY_LIST_COL_ICON,
	PLAY_LIST_COL_NAME,
	PLAY_LIST_COL_FULLNAME
} PlayListCol;


static gpointer play_list_control_parent_class = NULL;

GType play_list_control_get_type (void);
enum  {
	PLAY_LIST_CONTROL_DUMMY_PROPERTY,
	PLAY_LIST_CONTROL_PIPELINE,
	PLAY_LIST_CONTROL_VOLUME,
	PLAY_LIST_CONTROL_N_ROWS
};
void play_list_control_on_row_inserted (PlayListControl* self, GtkTreePath* row);
static void _play_list_control_on_row_inserted_gtk_tree_model_row_inserted (GtkListStore* _sender, GtkTreePath* path, GtkTreeIter* iter, gpointer self);
void play_list_control_on_row_deleted (PlayListControl* self, GtkTreePath* row);
static void _play_list_control_on_row_deleted_gtk_tree_model_row_deleted (GtkListStore* _sender, GtkTreePath* path, gpointer self);
PlayListControl* play_list_control_new (GtkListStore* store);
PlayListControl* play_list_control_construct (GType object_type, GtkListStore* store);
void play_list_control_set_location (PlayListControl* self, const char* location);
gboolean play_list_control_get_iter (PlayListControl* self, GtkTreeIter* iter);
GType play_list_col_get_type (void);
GstState play_list_control_get_state (PlayListControl* self);
gboolean play_list_control_play (PlayListControl* self);
gboolean play_list_control_pause (PlayListControl* self);
gboolean play_list_control_stop (PlayListControl* self);
gboolean play_list_control_move_to (PlayListControl* self, GtkTreePath* row);
gboolean play_list_control_prev (PlayListControl* self);
gboolean play_list_control_next (PlayListControl* self);
void play_list_control_seek (PlayListControl* self, gint64 location);
GstElement* play_list_control_get_pipeline (PlayListControl* self);
double play_list_control_get_volume (PlayListControl* self);
void play_list_control_set_volume (PlayListControl* self, double value);
guint play_list_control_get_n_rows (PlayListControl* self);
static GObject * play_list_control_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static void play_list_control_finalize (GObject* obj);
static void play_list_control_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void play_list_control_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);


static void g_cclosure_user_marshal_VOID__BOXED (GClosure * closure, GValue * return_value, guint n_param_values, const GValue * param_values, gpointer invocation_hint, gpointer marshal_data);

static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


static void _play_list_control_on_row_inserted_gtk_tree_model_row_inserted (GtkListStore* _sender, GtkTreePath* path, GtkTreeIter* iter, gpointer self) {
	play_list_control_on_row_inserted (self, path);
}


static void _play_list_control_on_row_deleted_gtk_tree_model_row_deleted (GtkListStore* _sender, GtkTreePath* path, gpointer self) {
	play_list_control_on_row_deleted (self, path);
}


PlayListControl* play_list_control_construct (GType object_type, GtkListStore* store) {
	PlayListControl * self;
	GtkListStore* _tmp0_;
	g_return_val_if_fail (store != NULL, NULL);
	self = g_object_newv (object_type, 0, NULL);
	self->playlist_store = (_tmp0_ = _g_object_ref0 (store), _g_object_unref0 (self->playlist_store), _tmp0_);
	g_signal_connect_object ((GtkTreeModel*) self->playlist_store, "row-inserted", (GCallback) _play_list_control_on_row_inserted_gtk_tree_model_row_inserted, self, 0);
	g_signal_connect_object ((GtkTreeModel*) self->playlist_store, "row-deleted", (GCallback) _play_list_control_on_row_deleted_gtk_tree_model_row_deleted, self, 0);
	return self;
}


PlayListControl* play_list_control_new (GtkListStore* store) {
	return play_list_control_construct (TYPE_PLAY_LIST_CONTROL, store);
}


void play_list_control_set_location (PlayListControl* self, const char* location) {
	char* _tmp0_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (location != NULL);
	g_object_set ((GObject*) self->player, "uri", _tmp0_ = g_strdup_printf ("file://%s", location), NULL, NULL);
	_g_free0 (_tmp0_);
}


gboolean play_list_control_play (PlayListControl* self) {
	gboolean result;
	GtkTreeIter iter = {0};
	char* filename;
	GstState state;
	g_return_val_if_fail (self != NULL, FALSE);
	if (!play_list_control_get_iter (self, &iter)) {
		result = FALSE;
		return result;
	}
	filename = NULL;
	gtk_tree_model_get ((GtkTreeModel*) self->playlist_store, &iter, PLAY_LIST_COL_FULLNAME, &filename, -1, -1);
	state = play_list_control_get_state (self);
	if (state == GST_STATE_NULL) {
		play_list_control_set_location (self, filename);
	}
	if (gst_element_set_state (self->player, GST_STATE_PLAYING) != GST_STATE_CHANGE_FAILURE) {
		gtk_list_store_set (self->playlist_store, &iter, PLAY_LIST_COL_ICON, GTK_STOCK_MEDIA_PLAY, -1, -1);
		g_signal_emit_by_name (self, "playing", &iter);
		result = TRUE;
		_g_free0 (filename);
		return result;
	}
	result = FALSE;
	_g_free0 (filename);
	return result;
}


gboolean play_list_control_pause (PlayListControl* self) {
	gboolean result;
	g_return_val_if_fail (self != NULL, FALSE);
	if (gst_element_set_state (self->player, GST_STATE_PAUSED) != GST_STATE_CHANGE_FAILURE) {
		GtkTreeIter iter = {0};
		if (play_list_control_get_iter (self, &iter)) {
			gtk_list_store_set (self->playlist_store, &iter, PLAY_LIST_COL_ICON, GTK_STOCK_MEDIA_PAUSE, -1, -1);
		}
		g_signal_emit_by_name (self, "paused", &iter);
		result = TRUE;
		return result;
	}
	result = FALSE;
	return result;
}


gboolean play_list_control_stop (PlayListControl* self) {
	gboolean result;
	g_return_val_if_fail (self != NULL, FALSE);
	if (gst_element_set_state (self->player, GST_STATE_NULL) != GST_STATE_CHANGE_FAILURE) {
		GtkTreeIter iter = {0};
		if (play_list_control_get_iter (self, &iter)) {
			gtk_list_store_set (self->playlist_store, &iter, PLAY_LIST_COL_ICON, NULL, -1, -1);
		}
		g_signal_emit_by_name (self, "stopped", &iter);
		result = TRUE;
		return result;
	}
	result = FALSE;
	return result;
}


gboolean play_list_control_prev (PlayListControl* self) {
	gboolean result;
	g_return_val_if_fail (self != NULL, FALSE);
	if (self->current_row == NULL) {
		result = FALSE;
		return result;
	}
	play_list_control_stop (self);
	if (gtk_tree_path_prev (self->current_row)) {
		result = play_list_control_move_to (self, self->current_row);
		return result;
	}
	result = FALSE;
	return result;
}


gboolean play_list_control_next (PlayListControl* self) {
	gboolean result;
	gint row_index;
	g_return_val_if_fail (self != NULL, FALSE);
	if (self->current_row == NULL) {
		result = FALSE;
		return result;
	}
	play_list_control_stop (self);
	row_index = gtk_tree_path_get_indices (self->current_row)[0];
	if (row_index < (self->number_of_rows - 1)) {
		gtk_tree_path_next (self->current_row);
		result = play_list_control_move_to (self, self->current_row);
		return result;
	}
	result = FALSE;
	return result;
}


static gpointer _gst_event_ref0 (gpointer self) {
	return self ? gst_event_ref (self) : NULL;
}


void play_list_control_seek (PlayListControl* self, gint64 location) {
	GstEvent* seek_event;
	g_return_if_fail (self != NULL);
	seek_event = gst_event_new_seek (1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_ACCURATE, GST_SEEK_TYPE_SET, location, GST_SEEK_TYPE_NONE, (gint64) 0);
	gst_element_send_event (self->player, _gst_event_ref0 (seek_event));
	_gst_event_unref0 (seek_event);
}


GstState play_list_control_get_state (PlayListControl* self) {
	GstState result;
	GstState state = 0;
	g_return_val_if_fail (self != NULL, 0);
	gst_element_get_state (self->player, &state, NULL, (GstClockTime) (GST_MSECOND * 50));
	result = state;
	return result;
}


static gpointer _gtk_tree_path_copy0 (gpointer self) {
	return self ? gtk_tree_path_copy (self) : NULL;
}


gboolean play_list_control_move_to (PlayListControl* self, GtkTreePath* row) {
	gboolean result;
	GtkTreeIter iter = {0};
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (row != NULL, FALSE);
	if (gtk_tree_model_get_iter ((GtkTreeModel*) self->playlist_store, &iter, row)) {
		GtkTreePath* _tmp0_;
		self->current_row = (_tmp0_ = _gtk_tree_path_copy0 (row), _gtk_tree_path_free0 (self->current_row), _tmp0_);
		g_signal_emit_by_name (self, "moved", &iter);
		result = TRUE;
		return result;
	}
	result = FALSE;
	return result;
}


gboolean play_list_control_get_iter (PlayListControl* self, GtkTreeIter* iter) {
	gboolean result;
	g_return_val_if_fail (self != NULL, FALSE);
	if (self->current_row == NULL) {
		result = FALSE;
		return result;
	}
	if (!gtk_tree_model_get_iter ((GtkTreeModel*) self->playlist_store, iter, self->current_row)) {
		result = FALSE;
		return result;
	}
	result = TRUE;
	return result;
}


void play_list_control_on_row_deleted (PlayListControl* self, GtkTreePath* row) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (row != NULL);
	self->number_of_rows--;
	if (self->current_row == NULL) {
		return;
	}
	if (gtk_tree_path_compare (self->current_row, row) == 0) {
		play_list_control_stop (self);
	}
}


void play_list_control_on_row_inserted (PlayListControl* self, GtkTreePath* row) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (row != NULL);
	self->number_of_rows++;
}


GstElement* play_list_control_get_pipeline (PlayListControl* self) {
	GstElement* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->player;
	return result;
}


double play_list_control_get_volume (PlayListControl* self) {
	double result;
	double value = 0.0;
	g_return_val_if_fail (self != NULL, 0.0);
	g_object_get ((GObject*) self->player, "volume", &value, NULL, NULL);
	result = value;
	return result;
}


void play_list_control_set_volume (PlayListControl* self, double value) {
	g_return_if_fail (self != NULL);
	g_object_set ((GObject*) self->player, "volume", value, NULL, NULL);
	g_object_notify ((GObject *) self, "volume");
}


guint play_list_control_get_n_rows (PlayListControl* self) {
	guint result;
	g_return_val_if_fail (self != NULL, 0U);
	result = (guint) self->number_of_rows;
	return result;
}


static GObject * play_list_control_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GObjectClass * parent_class;
	PlayListControl * self;
	parent_class = G_OBJECT_CLASS (play_list_control_parent_class);
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = PLAY_LIST_CONTROL (obj);
	{
		GstElement* _tmp0_;
		self->player = (_tmp0_ = gst_element_factory_make ("playbin2", "player"), _gst_object_unref0 (self->player), _tmp0_);
	}
	return obj;
}


static void play_list_control_class_init (PlayListControlClass * klass) {
	play_list_control_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->get_property = play_list_control_get_property;
	G_OBJECT_CLASS (klass)->set_property = play_list_control_set_property;
	G_OBJECT_CLASS (klass)->constructor = play_list_control_constructor;
	G_OBJECT_CLASS (klass)->finalize = play_list_control_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), PLAY_LIST_CONTROL_PIPELINE, g_param_spec_object ("pipeline", "pipeline", "pipeline", GST_TYPE_ELEMENT, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), PLAY_LIST_CONTROL_VOLUME, g_param_spec_double ("volume", "volume", "volume", -G_MAXDOUBLE, G_MAXDOUBLE, 0.0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), PLAY_LIST_CONTROL_N_ROWS, g_param_spec_uint ("n-rows", "n-rows", "n-rows", 0, G_MAXUINT, 0U, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE));
	g_signal_new ("playing", TYPE_PLAY_LIST_CONTROL, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_user_marshal_VOID__BOXED, G_TYPE_NONE, 1, GTK_TYPE_TREE_ITER);
	g_signal_new ("paused", TYPE_PLAY_LIST_CONTROL, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_user_marshal_VOID__BOXED, G_TYPE_NONE, 1, GTK_TYPE_TREE_ITER);
	g_signal_new ("stopped", TYPE_PLAY_LIST_CONTROL, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_user_marshal_VOID__BOXED, G_TYPE_NONE, 1, GTK_TYPE_TREE_ITER);
	g_signal_new ("moved", TYPE_PLAY_LIST_CONTROL, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_user_marshal_VOID__BOXED, G_TYPE_NONE, 1, GTK_TYPE_TREE_ITER);
}


static void play_list_control_instance_init (PlayListControl * self) {
}


static void play_list_control_finalize (GObject* obj) {
	PlayListControl * self;
	self = PLAY_LIST_CONTROL (obj);
	_gst_object_unref0 (self->player);
	_g_object_unref0 (self->playlist_store);
	_gtk_tree_path_free0 (self->current_row);
	G_OBJECT_CLASS (play_list_control_parent_class)->finalize (obj);
}


GType play_list_control_get_type (void) {
	static GType play_list_control_type_id = 0;
	if (play_list_control_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (PlayListControlClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) play_list_control_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (PlayListControl), 0, (GInstanceInitFunc) play_list_control_instance_init, NULL };
		play_list_control_type_id = g_type_register_static (G_TYPE_OBJECT, "PlayListControl", &g_define_type_info, 0);
	}
	return play_list_control_type_id;
}


static void play_list_control_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	PlayListControl * self;
	self = PLAY_LIST_CONTROL (object);
	switch (property_id) {
		case PLAY_LIST_CONTROL_PIPELINE:
		g_value_set_object (value, play_list_control_get_pipeline (self));
		break;
		case PLAY_LIST_CONTROL_VOLUME:
		g_value_set_double (value, play_list_control_get_volume (self));
		break;
		case PLAY_LIST_CONTROL_N_ROWS:
		g_value_set_uint (value, play_list_control_get_n_rows (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void play_list_control_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	PlayListControl * self;
	self = PLAY_LIST_CONTROL (object);
	switch (property_id) {
		case PLAY_LIST_CONTROL_VOLUME:
		play_list_control_set_volume (self, g_value_get_double (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}



static void g_cclosure_user_marshal_VOID__BOXED (GClosure * closure, GValue * return_value, guint n_param_values, const GValue * param_values, gpointer invocation_hint, gpointer marshal_data) {
	typedef void (*GMarshalFunc_VOID__BOXED) (gpointer data1, gpointer arg_1, gpointer data2);
	register GMarshalFunc_VOID__BOXED callback;
	register GCClosure * cc;
	register gpointer data1, data2;
	cc = (GCClosure *) closure;
	g_return_if_fail (n_param_values == 2);
	if (G_CCLOSURE_SWAP_DATA (closure)) {
		data1 = closure->data;
		data2 = param_values->data[0].v_pointer;
	} else {
		data1 = param_values->data[0].v_pointer;
		data2 = closure->data;
	}
	callback = (GMarshalFunc_VOID__BOXED) (marshal_data ? marshal_data : cc->callback);
	callback (data1, g_value_get_boxed (param_values + 1), data2);
}



