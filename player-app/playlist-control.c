/* playlist-control.c generated by valac, the Vala compiler
 * generated from playlist-control.gs, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <common.h>
#include <gtk/gtk.h>
#include <gst/gst.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>


#define OMAP_TYPE_PLAY_LIST_CONTROL (omap_play_list_control_get_type ())
#define OMAP_PLAY_LIST_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), OMAP_TYPE_PLAY_LIST_CONTROL, OmapPlayListControl))
#define OMAP_PLAY_LIST_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), OMAP_TYPE_PLAY_LIST_CONTROL, OmapPlayListControlClass))
#define OMAP_IS_PLAY_LIST_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), OMAP_TYPE_PLAY_LIST_CONTROL))
#define OMAP_IS_PLAY_LIST_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), OMAP_TYPE_PLAY_LIST_CONTROL))
#define OMAP_PLAY_LIST_CONTROL_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), OMAP_TYPE_PLAY_LIST_CONTROL, OmapPlayListControlClass))

typedef struct _OmapPlayListControl OmapPlayListControl;
typedef struct _OmapPlayListControlClass OmapPlayListControlClass;
typedef struct _OmapPlayListControlPrivate OmapPlayListControlPrivate;

#define OMAP_PLAY_LIST_CONTROL_TYPE_COL (omap_play_list_control_col_get_type ())
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _gtk_tree_path_free0(var) ((var == NULL) ? NULL : (var = (gtk_tree_path_free (var), NULL)))
#define _gst_object_unref0(var) ((var == NULL) ? NULL : (var = (gst_object_unref (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))

struct _OmapPlayListControl {
	OmapMediaControl parent_instance;
	OmapPlayListControlPrivate * priv;
	GtkListStore* playlist_store;
	GtkTreePath* current_row;
	gint number_of_rows;
	GstBin* player;
};

struct _OmapPlayListControlClass {
	OmapMediaControlClass parent_class;
};

typedef enum  {
	OMAP_PLAY_LIST_CONTROL_COL_ICON,
	OMAP_PLAY_LIST_CONTROL_COL_TITLE,
	OMAP_PLAY_LIST_CONTROL_COL_ARTIST,
	OMAP_PLAY_LIST_CONTROL_COL_ALBUM,
	OMAP_PLAY_LIST_CONTROL_COL_FILE
} OmapPlayListControlCol;


static gpointer omap_play_list_control_parent_class = NULL;

GType omap_play_list_control_get_type (void);
enum  {
	OMAP_PLAY_LIST_CONTROL_DUMMY_PROPERTY,
	OMAP_PLAY_LIST_CONTROL_VOLUME,
	OMAP_PLAY_LIST_CONTROL_N_ROWS,
	OMAP_PLAY_LIST_CONTROL_LOCATION
};
GType omap_play_list_control_col_get_type (void);
void omap_play_list_control_on_row_inserted (OmapPlayListControl* self, GtkTreePath* row);
static void _omap_play_list_control_on_row_inserted_gtk_tree_model_row_inserted (GtkListStore* _sender, GtkTreePath* path, GtkTreeIter* iter, gpointer self);
void omap_play_list_control_on_row_deleted (OmapPlayListControl* self, GtkTreePath* row);
static void _omap_play_list_control_on_row_deleted_gtk_tree_model_row_deleted (GtkListStore* _sender, GtkTreePath* path, gpointer self);
OmapPlayListControl* omap_play_list_control_new (GtkListStore* store);
OmapPlayListControl* omap_play_list_control_construct (GType object_type, GtkListStore* store);
gboolean omap_play_list_control_get_iter (OmapPlayListControl* self, GtkTreeIter* iter);
void omap_play_list_control_set_location (OmapPlayListControl* self, const char* value);
char* omap_play_list_control_iter_get_title (OmapPlayListControl* self, GtkTreeIter* iter);
gboolean omap_play_list_control_play (OmapPlayListControl* self);
gboolean omap_play_list_control_pause (OmapPlayListControl* self);
gboolean omap_play_list_control_stop (OmapPlayListControl* self);
gboolean omap_play_list_control_move_to (OmapPlayListControl* self, GtkTreePath* row);
gboolean omap_play_list_control_prev (OmapPlayListControl* self);
gboolean omap_play_list_control_next (OmapPlayListControl* self);
void omap_play_list_control_add_file (OmapPlayListControl* self, const char* file);
void omap_play_list_control_on_tag_found (OmapPlayListControl* self, const char* tag_name, GValue* tag_value);
gint omap_play_list_control_get_icon_column (void);
gint omap_play_list_control_get_title_column (void);
gint omap_play_list_control_get_artist_column (void);
gint omap_play_list_control_get_album_column (void);
char* omap_play_list_control_iter_get_file (OmapPlayListControl* self, GtkTreeIter* iter);
GtkListStore* omap_play_list_control_model_new (void);
static inline double _dynamic_get_volume0 (GstBin* obj);
double omap_play_list_control_get_volume (OmapPlayListControl* self);
static inline void _dynamic_set_volume1 (GstBin* obj, double value);
void omap_play_list_control_set_volume (OmapPlayListControl* self, double value);
guint omap_play_list_control_get_n_rows (OmapPlayListControl* self);
static inline void _dynamic_set_uri2 (GstBin* obj, char* value);
static void _omap_play_list_control_on_tag_found_omap_media_control_tag_found (OmapPlayListControl* _sender, const char* name, GValue* tag_value, gpointer self);
static GObject * omap_play_list_control_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static void omap_play_list_control_finalize (GObject* obj);
static void omap_play_list_control_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void omap_play_list_control_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);


static void g_cclosure_user_marshal_VOID__BOXED (GClosure * closure, GValue * return_value, guint n_param_values, const GValue * param_values, gpointer invocation_hint, gpointer marshal_data);

GType omap_play_list_control_col_get_type (void) {
	static volatile gsize omap_play_list_control_col_type_id__volatile = 0;
	if (g_once_init_enter (&omap_play_list_control_col_type_id__volatile)) {
		static const GEnumValue values[] = {{OMAP_PLAY_LIST_CONTROL_COL_ICON, "OMAP_PLAY_LIST_CONTROL_COL_ICON", "icon"}, {OMAP_PLAY_LIST_CONTROL_COL_TITLE, "OMAP_PLAY_LIST_CONTROL_COL_TITLE", "title"}, {OMAP_PLAY_LIST_CONTROL_COL_ARTIST, "OMAP_PLAY_LIST_CONTROL_COL_ARTIST", "artist"}, {OMAP_PLAY_LIST_CONTROL_COL_ALBUM, "OMAP_PLAY_LIST_CONTROL_COL_ALBUM", "album"}, {OMAP_PLAY_LIST_CONTROL_COL_FILE, "OMAP_PLAY_LIST_CONTROL_COL_FILE", "file"}, {0, NULL, NULL}};
		GType omap_play_list_control_col_type_id;
		omap_play_list_control_col_type_id = g_enum_register_static ("OmapPlayListControlCol", values);
		g_once_init_leave (&omap_play_list_control_col_type_id__volatile, omap_play_list_control_col_type_id);
	}
	return omap_play_list_control_col_type_id__volatile;
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


static void _omap_play_list_control_on_row_inserted_gtk_tree_model_row_inserted (GtkListStore* _sender, GtkTreePath* path, GtkTreeIter* iter, gpointer self) {
	omap_play_list_control_on_row_inserted (self, path);
}


static void _omap_play_list_control_on_row_deleted_gtk_tree_model_row_deleted (GtkListStore* _sender, GtkTreePath* path, gpointer self) {
	omap_play_list_control_on_row_deleted (self, path);
}


OmapPlayListControl* omap_play_list_control_construct (GType object_type, GtkListStore* store) {
	OmapPlayListControl * self;
	GtkListStore* _tmp0_;
	g_return_val_if_fail (store != NULL, NULL);
	self = g_object_newv (object_type, 0, NULL);
	self->playlist_store = (_tmp0_ = _g_object_ref0 (store), _g_object_unref0 (self->playlist_store), _tmp0_);
	g_signal_connect_object ((GtkTreeModel*) self->playlist_store, "row-inserted", (GCallback) _omap_play_list_control_on_row_inserted_gtk_tree_model_row_inserted, self, 0);
	g_signal_connect_object ((GtkTreeModel*) self->playlist_store, "row-deleted", (GCallback) _omap_play_list_control_on_row_deleted_gtk_tree_model_row_deleted, self, 0);
	return self;
}


OmapPlayListControl* omap_play_list_control_new (GtkListStore* store) {
	return omap_play_list_control_construct (OMAP_TYPE_PLAY_LIST_CONTROL, store);
}


gboolean omap_play_list_control_play (OmapPlayListControl* self) {
	gboolean result = FALSE;
	GtkTreeIter iter = {0};
	char* filename;
	g_return_val_if_fail (self != NULL, FALSE);
	if (!omap_play_list_control_get_iter (self, &iter)) {
		result = FALSE;
		return result;
	}
	filename = NULL;
	gtk_tree_model_get ((GtkTreeModel*) self->playlist_store, &iter, OMAP_PLAY_LIST_CONTROL_COL_FILE, &filename, -1, -1);
	if (omap_media_control_get_state ((OmapMediaControl*) self) == GST_STATE_NULL) {
		omap_play_list_control_set_location (self, filename);
	}
	if (gst_element_set_state ((GstElement*) omap_media_control_get_pipeline ((OmapMediaControl*) self), GST_STATE_PLAYING) != GST_STATE_CHANGE_FAILURE) {
		char* _tmp0_;
		gtk_list_store_set (self->playlist_store, &iter, OMAP_PLAY_LIST_CONTROL_COL_ICON, GTK_STOCK_MEDIA_PLAY, -1, -1);
		g_signal_emit_by_name (self, "title-changed", _tmp0_ = omap_play_list_control_iter_get_title (self, &iter));
		_g_free0 (_tmp0_);
		g_signal_emit_by_name (self, "playing", &iter);
		result = TRUE;
		_g_free0 (filename);
		return result;
	}
	result = FALSE;
	_g_free0 (filename);
	return result;
}


gboolean omap_play_list_control_pause (OmapPlayListControl* self) {
	gboolean result = FALSE;
	g_return_val_if_fail (self != NULL, FALSE);
	if (gst_element_set_state ((GstElement*) omap_media_control_get_pipeline ((OmapMediaControl*) self), GST_STATE_PAUSED) != GST_STATE_CHANGE_FAILURE) {
		GtkTreeIter iter = {0};
		if (omap_play_list_control_get_iter (self, &iter)) {
			gtk_list_store_set (self->playlist_store, &iter, OMAP_PLAY_LIST_CONTROL_COL_ICON, GTK_STOCK_MEDIA_PAUSE, -1, -1);
		}
		g_signal_emit_by_name (self, "paused", &iter);
		result = TRUE;
		return result;
	}
	result = FALSE;
	return result;
}


gboolean omap_play_list_control_stop (OmapPlayListControl* self) {
	gboolean result = FALSE;
	g_return_val_if_fail (self != NULL, FALSE);
	if (gst_element_set_state ((GstElement*) omap_media_control_get_pipeline ((OmapMediaControl*) self), GST_STATE_NULL) != GST_STATE_CHANGE_FAILURE) {
		GtkTreeIter iter = {0};
		if (omap_play_list_control_get_iter (self, &iter)) {
			gtk_list_store_set (self->playlist_store, &iter, OMAP_PLAY_LIST_CONTROL_COL_ICON, NULL, -1, -1);
		}
		g_signal_emit_by_name (self, "stopped", &iter);
		result = TRUE;
		return result;
	}
	result = FALSE;
	return result;
}


gboolean omap_play_list_control_prev (OmapPlayListControl* self) {
	gboolean result = FALSE;
	g_return_val_if_fail (self != NULL, FALSE);
	if (self->current_row == NULL) {
		result = FALSE;
		return result;
	}
	omap_play_list_control_stop (self);
	if (gtk_tree_path_prev (self->current_row)) {
		result = omap_play_list_control_move_to (self, self->current_row);
		return result;
	}
	result = FALSE;
	return result;
}


gboolean omap_play_list_control_next (OmapPlayListControl* self) {
	gboolean result = FALSE;
	gint row_index;
	g_return_val_if_fail (self != NULL, FALSE);
	if (self->current_row == NULL) {
		result = FALSE;
		return result;
	}
	omap_play_list_control_stop (self);
	row_index = gtk_tree_path_get_indices (self->current_row)[0];
	if (row_index < (self->number_of_rows - 1)) {
		gtk_tree_path_next (self->current_row);
		result = omap_play_list_control_move_to (self, self->current_row);
		return result;
	}
	result = FALSE;
	return result;
}


void omap_play_list_control_add_file (OmapPlayListControl* self, const char* file) {
	char* _tmp0_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (file != NULL);
	gtk_list_store_insert_with_values (self->playlist_store, NULL, -1, OMAP_PLAY_LIST_CONTROL_COL_TITLE, _tmp0_ = g_filename_display_basename (file), OMAP_PLAY_LIST_CONTROL_COL_FILE, file, -1, -1);
	_g_free0 (_tmp0_);
}


static gpointer _gtk_tree_path_copy0 (gpointer self) {
	return self ? gtk_tree_path_copy (self) : NULL;
}


gboolean omap_play_list_control_move_to (OmapPlayListControl* self, GtkTreePath* row) {
	gboolean result = FALSE;
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


gboolean omap_play_list_control_get_iter (OmapPlayListControl* self, GtkTreeIter* iter) {
	gboolean result = FALSE;
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


void omap_play_list_control_on_row_deleted (OmapPlayListControl* self, GtkTreePath* row) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (row != NULL);
	self->number_of_rows--;
	if (self->current_row == NULL) {
		return;
	}
	if (gtk_tree_path_compare (self->current_row, row) == 0) {
		omap_play_list_control_stop (self);
	}
}


void omap_play_list_control_on_tag_found (OmapPlayListControl* self, const char* tag_name, GValue* tag_value) {
	OmapPlayListControlCol column = 0;
	gboolean is_title;
	GQuark _tmp1_;
	const char* _tmp0_;
	char* column_value;
	GtkTreeIter iter = {0};
	g_return_if_fail (self != NULL);
	g_return_if_fail (tag_name != NULL);
	is_title = FALSE;
	_tmp0_ = tag_name;
	_tmp1_ = (NULL == _tmp0_) ? 0 : g_quark_from_string (_tmp0_);
	if (_tmp1_ == g_quark_from_string (GST_TAG_TITLE))
	switch (0) {
		default:
		{
			{
				column = OMAP_PLAY_LIST_CONTROL_COL_TITLE;
				is_title = TRUE;
			}
			break;
		}
	} else if (_tmp1_ == g_quark_from_string (GST_TAG_ARTIST))
	switch (0) {
		default:
		{
			{
				column = OMAP_PLAY_LIST_CONTROL_COL_ARTIST;
			}
			break;
		}
	} else if (_tmp1_ == g_quark_from_string (GST_TAG_ALBUM))
	switch (0) {
		default:
		{
			{
				column = OMAP_PLAY_LIST_CONTROL_COL_ALBUM;
			}
			break;
		}
	} else
	switch (0) {
		default:
		{
			{
				return;
			}
			break;
		}
	}
	column_value = g_strdup (g_value_get_string (tag_value));
	gtk_tree_model_get_iter ((GtkTreeModel*) self->playlist_store, &iter, self->current_row);
	gtk_list_store_set (self->playlist_store, &iter, column, column_value, -1, -1);
	if (is_title) {
		g_signal_emit_by_name (self, "title-changed", column_value);
	}
	_g_free0 (column_value);
}


void omap_play_list_control_on_row_inserted (OmapPlayListControl* self, GtkTreePath* row) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (row != NULL);
	self->number_of_rows++;
}


gint omap_play_list_control_get_icon_column (void) {
	gint result = 0;
	result = (gint) OMAP_PLAY_LIST_CONTROL_COL_ICON;
	return result;
}


gint omap_play_list_control_get_title_column (void) {
	gint result = 0;
	result = (gint) OMAP_PLAY_LIST_CONTROL_COL_TITLE;
	return result;
}


gint omap_play_list_control_get_artist_column (void) {
	gint result = 0;
	result = (gint) OMAP_PLAY_LIST_CONTROL_COL_ARTIST;
	return result;
}


gint omap_play_list_control_get_album_column (void) {
	gint result = 0;
	result = (gint) OMAP_PLAY_LIST_CONTROL_COL_ALBUM;
	return result;
}


char* omap_play_list_control_iter_get_title (OmapPlayListControl* self, GtkTreeIter* iter) {
	char* result = NULL;
	char* name;
	g_return_val_if_fail (self != NULL, NULL);
	name = NULL;
	gtk_tree_model_get ((GtkTreeModel*) self->playlist_store, iter, OMAP_PLAY_LIST_CONTROL_COL_TITLE, &name, -1, -1);
	result = name;
	return result;
}


char* omap_play_list_control_iter_get_file (OmapPlayListControl* self, GtkTreeIter* iter) {
	char* result = NULL;
	char* file;
	g_return_val_if_fail (self != NULL, NULL);
	file = NULL;
	gtk_tree_model_get ((GtkTreeModel*) self->playlist_store, iter, OMAP_PLAY_LIST_CONTROL_COL_FILE, &file, -1, -1);
	result = file;
	return result;
}


GtkListStore* omap_play_list_control_model_new (void) {
	GtkListStore* result = NULL;
	GType s;
	s = G_TYPE_STRING;
	result = gtk_list_store_new (5, s, s, s, s, s, NULL);
	return result;
}


static inline double _dynamic_get_volume0 (GstBin* obj) {
	double result;
	g_object_get (obj, "volume", &result, NULL);
	return result;
}


double omap_play_list_control_get_volume (OmapPlayListControl* self) {
	double result;
	g_return_val_if_fail (self != NULL, 0.0);
	result = _dynamic_get_volume0 (self->player);
	return result;
}


static inline void _dynamic_set_volume1 (GstBin* obj, double value) {
	g_object_set (obj, "volume", value, NULL);
}


void omap_play_list_control_set_volume (OmapPlayListControl* self, double value) {
	g_return_if_fail (self != NULL);
	_dynamic_set_volume1 (self->player, value);
	g_object_notify ((GObject *) self, "volume");
}


guint omap_play_list_control_get_n_rows (OmapPlayListControl* self) {
	guint result;
	g_return_val_if_fail (self != NULL, 0U);
	result = (guint) self->number_of_rows;
	return result;
}


static inline void _dynamic_set_uri2 (GstBin* obj, char* value) {
	g_object_set (obj, "uri", value, NULL);
}


void omap_play_list_control_set_location (OmapPlayListControl* self, const char* value) {
	char* _tmp0_;
	g_return_if_fail (self != NULL);
	_dynamic_set_uri2 (self->player, _tmp0_ = g_strdup_printf ("file://%s", value));
	_g_free0 (_tmp0_);
	g_object_notify ((GObject *) self, "location");
}


static void _omap_play_list_control_on_tag_found_omap_media_control_tag_found (OmapPlayListControl* _sender, const char* name, GValue* tag_value, gpointer self) {
	omap_play_list_control_on_tag_found (self, name, tag_value);
}


static GObject * omap_play_list_control_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GObjectClass * parent_class;
	OmapPlayListControl * self;
	parent_class = G_OBJECT_CLASS (omap_play_list_control_parent_class);
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = OMAP_PLAY_LIST_CONTROL (obj);
	{
		GstBin* _tmp1_;
		GstElement* _tmp0_;
		g_signal_connect_object ((OmapMediaControl*) self, "tag-found", (GCallback) _omap_play_list_control_on_tag_found_omap_media_control_tag_found, self, 0);
		self->player = (_tmp1_ = (_tmp0_ = gst_element_factory_make ("playbin2", "player"), GST_IS_BIN (_tmp0_) ? ((GstBin*) _tmp0_) : NULL), _gst_object_unref0 (self->player), _tmp1_);
		if (self->player == NULL) {
			GstBin* _tmp3_;
			GstElement* _tmp2_;
			self->player = (_tmp3_ = (_tmp2_ = gst_element_factory_make ("playbin", "player"), GST_IS_BIN (_tmp2_) ? ((GstBin*) _tmp2_) : NULL), _gst_object_unref0 (self->player), _tmp3_);
		}
		omap_media_control_set_pipeline ((OmapMediaControl*) self, self->player);
	}
	return obj;
}


static void omap_play_list_control_class_init (OmapPlayListControlClass * klass) {
	omap_play_list_control_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->get_property = omap_play_list_control_get_property;
	G_OBJECT_CLASS (klass)->set_property = omap_play_list_control_set_property;
	G_OBJECT_CLASS (klass)->constructor = omap_play_list_control_constructor;
	G_OBJECT_CLASS (klass)->finalize = omap_play_list_control_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), OMAP_PLAY_LIST_CONTROL_VOLUME, g_param_spec_double ("volume", "volume", "volume", -G_MAXDOUBLE, G_MAXDOUBLE, 0.0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), OMAP_PLAY_LIST_CONTROL_N_ROWS, g_param_spec_uint ("n-rows", "n-rows", "n-rows", 0, G_MAXUINT, 0U, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), OMAP_PLAY_LIST_CONTROL_LOCATION, g_param_spec_string ("location", "location", "location", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_WRITABLE));
	g_signal_new ("playing", OMAP_TYPE_PLAY_LIST_CONTROL, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_user_marshal_VOID__BOXED, G_TYPE_NONE, 1, GTK_TYPE_TREE_ITER);
	g_signal_new ("paused", OMAP_TYPE_PLAY_LIST_CONTROL, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_user_marshal_VOID__BOXED, G_TYPE_NONE, 1, GTK_TYPE_TREE_ITER);
	g_signal_new ("stopped", OMAP_TYPE_PLAY_LIST_CONTROL, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_user_marshal_VOID__BOXED, G_TYPE_NONE, 1, GTK_TYPE_TREE_ITER);
	g_signal_new ("moved", OMAP_TYPE_PLAY_LIST_CONTROL, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_user_marshal_VOID__BOXED, G_TYPE_NONE, 1, GTK_TYPE_TREE_ITER);
	g_signal_new ("title_changed", OMAP_TYPE_PLAY_LIST_CONTROL, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__STRING, G_TYPE_NONE, 1, G_TYPE_STRING);
}


static void omap_play_list_control_instance_init (OmapPlayListControl * self) {
}


static void omap_play_list_control_finalize (GObject* obj) {
	OmapPlayListControl * self;
	self = OMAP_PLAY_LIST_CONTROL (obj);
	_g_object_unref0 (self->playlist_store);
	_gtk_tree_path_free0 (self->current_row);
	_gst_object_unref0 (self->player);
	G_OBJECT_CLASS (omap_play_list_control_parent_class)->finalize (obj);
}


GType omap_play_list_control_get_type (void) {
	static volatile gsize omap_play_list_control_type_id__volatile = 0;
	if (g_once_init_enter (&omap_play_list_control_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (OmapPlayListControlClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) omap_play_list_control_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (OmapPlayListControl), 0, (GInstanceInitFunc) omap_play_list_control_instance_init, NULL };
		GType omap_play_list_control_type_id;
		omap_play_list_control_type_id = g_type_register_static (OMAP_TYPE_MEDIA_CONTROL, "OmapPlayListControl", &g_define_type_info, 0);
		g_once_init_leave (&omap_play_list_control_type_id__volatile, omap_play_list_control_type_id);
	}
	return omap_play_list_control_type_id__volatile;
}


static void omap_play_list_control_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	OmapPlayListControl * self;
	self = OMAP_PLAY_LIST_CONTROL (object);
	switch (property_id) {
		case OMAP_PLAY_LIST_CONTROL_VOLUME:
		g_value_set_double (value, omap_play_list_control_get_volume (self));
		break;
		case OMAP_PLAY_LIST_CONTROL_N_ROWS:
		g_value_set_uint (value, omap_play_list_control_get_n_rows (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void omap_play_list_control_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	OmapPlayListControl * self;
	self = OMAP_PLAY_LIST_CONTROL (object);
	switch (property_id) {
		case OMAP_PLAY_LIST_CONTROL_VOLUME:
		omap_play_list_control_set_volume (self, g_value_get_double (value));
		break;
		case OMAP_PLAY_LIST_CONTROL_LOCATION:
		omap_play_list_control_set_location (self, g_value_get_string (value));
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



