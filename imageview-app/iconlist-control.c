/* iconlist-control.c generated by valac, the Vala compiler
 * generated from iconlist-control.gs, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <gst/gst.h>
#include <gdk-pixbuf/gdk-pixdata.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <gio/gio.h>


#define TYPE_MEDIA_CONTROL (media_control_get_type ())
#define MEDIA_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_MEDIA_CONTROL, MediaControl))
#define MEDIA_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_MEDIA_CONTROL, MediaControlClass))
#define IS_MEDIA_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_MEDIA_CONTROL))
#define IS_MEDIA_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_MEDIA_CONTROL))
#define MEDIA_CONTROL_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_MEDIA_CONTROL, MediaControlClass))

typedef struct _MediaControl MediaControl;
typedef struct _MediaControlClass MediaControlClass;
typedef struct _MediaControlPrivate MediaControlPrivate;

#define TYPE_ICON_LIST_CONTROL (icon_list_control_get_type ())
#define ICON_LIST_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_ICON_LIST_CONTROL, IconListControl))
#define ICON_LIST_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_ICON_LIST_CONTROL, IconListControlClass))
#define IS_ICON_LIST_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_ICON_LIST_CONTROL))
#define IS_ICON_LIST_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_ICON_LIST_CONTROL))
#define ICON_LIST_CONTROL_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_ICON_LIST_CONTROL, IconListControlClass))

typedef struct _IconListControl IconListControl;
typedef struct _IconListControlClass IconListControlClass;
typedef struct _IconListControlPrivate IconListControlPrivate;

#define ICON_LIST_CONTROL_TYPE_COL (icon_list_control_col_get_type ())
#define _gst_object_unref0(var) ((var == NULL) ? NULL : (var = (gst_object_unref (var), NULL)))
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_error_free0(var) ((var == NULL) ? NULL : (var = (g_error_free (var), NULL)))
#define _gtk_icon_info_free0(var) ((var == NULL) ? NULL : (var = (gtk_icon_info_free (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))
#define __g_list_free_g_object_unref0(var) ((var == NULL) ? NULL : (var = (_g_list_free_g_object_unref (var), NULL)))
typedef struct _IconListControlAddFolderData IconListControlAddFolderData;
#define _gtk_tree_path_free0(var) ((var == NULL) ? NULL : (var = (gtk_tree_path_free (var), NULL)))
typedef struct _IconListControlFillIconsData IconListControlFillIconsData;

struct _MediaControl {
	GObject parent_instance;
	MediaControlPrivate * priv;
	GstBus* bus;
	GstBin* pipeline;
};

struct _MediaControlClass {
	GObjectClass parent_class;
};

struct _IconListControl {
	MediaControl parent_instance;
	IconListControlPrivate * priv;
	GstElement* filesrc;
	GstElement* imagesink;
	GdkPixbuf* missing_pixbuf;
	GSourceFunc continuation;
	gpointer continuation_target;
	GDestroyNotify continuation_target_destroy_notify;
	GError* continuation_error;
};

struct _IconListControlClass {
	MediaControlClass parent_class;
};

struct _IconListControlPrivate {
	GtkListStore* _iconlist_store;
};

typedef enum  {
	ICON_LIST_CONTROL_COL_TEXT,
	ICON_LIST_CONTROL_COL_FILE,
	ICON_LIST_CONTROL_COL_PIXBUF,
	ICON_LIST_CONTROL_COL_VALID,
	ICON_LIST_CONTROL_COL_FILLED
} IconListControlCol;

struct _IconListControlAddFolderData {
	int _state_;
	GAsyncResult* _res_;
	GSimpleAsyncResult* _async_result;
	IconListControl* self;
	char* dirname;
	GCancellable* cancellable;
	GFile* dir;
	GFileEnumerator* file_etor;
	GList* next_files;
	char* _tmp0_;
	GError * e1;
	GError * _inner_error_;
};

struct _IconListControlFillIconsData {
	int _state_;
	GAsyncResult* _res_;
	GSimpleAsyncResult* _async_result;
	IconListControl* self;
	GtkTreePath* path;
	GtkTreePath* end;
	GCancellable* cancellable;
	GSourceFunc _tmp0_;
	gboolean _tmp1_;
	gboolean _tmp2_;
	GtkTreeIter iter;
	char* file;
	gboolean filled;
	GError* _tmp3_;
	GdkPixbuf* pixbuf;
	gboolean valid;
	gboolean _tmp4_;
	GdkPixbuf* _tmp6_;
	GdkPixbuf* _tmp5_;
	GdkPixbuf* _tmp7_;
};


extern GdkPixbuf* icon_list_control_loading_pixbuf;
GdkPixbuf* icon_list_control_loading_pixbuf = NULL;
extern GdkPixbuf* icon_list_control_last_pixbuf;
GdkPixbuf* icon_list_control_last_pixbuf = NULL;
extern GQuark icon_list_control_pixbuf_q;
GQuark icon_list_control_pixbuf_q = 0U;
extern gboolean icon_list_control_pixbufs_loaded;
gboolean icon_list_control_pixbufs_loaded = FALSE;
static gpointer icon_list_control_parent_class = NULL;

#define ICON_PIPELINE_DESC "filesrc name=filesrc ! jpegdec ! ffmpegcolorspace ! videoscale !\nvideo/x-raw-rgb,width=128,height=96 ! gdkpixbufsink name=imagesink"
#define IMAGE_FILE_ATTRIBUTES "standard::name,standard::display-name,standard::content-type"
GType media_control_get_type (void);
GType icon_list_control_get_type (void);
#define ICON_LIST_CONTROL_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_ICON_LIST_CONTROL, IconListControlPrivate))
enum  {
	ICON_LIST_CONTROL_DUMMY_PROPERTY,
	ICON_LIST_CONTROL_ICONLIST_STORE
};
GType icon_list_control_col_get_type (void);
void icon_list_control_set_iconlist_store (IconListControl* self, GtkListStore* value);
void icon_list_control_setup_icons (IconListControl* self, GError** error);
void icon_list_control_setup_elements (IconListControl* self, GError** error);
IconListControl* icon_list_control_new (GtkListStore* model, GError** error);
IconListControl* icon_list_control_construct (GType object_type, GtkListStore* model, GError** error);
void icon_list_control_setup_pipeline (IconListControl* self, GError** error);
void media_control_set_pipeline (MediaControl* self, GstBin* bin);
void icon_list_control_on_structure (IconListControl* self, GstObject* src, const char* name);
static void _icon_list_control_on_structure_media_control_structure_message (IconListControl* _sender, GstObject* src, const char* name, gpointer self);
static void icon_list_control_add_folder_data_free (gpointer _data);
static void icon_list_control_add_folder_ready (GObject* source_object, GAsyncResult* _res_, gpointer _user_data_);
static void _g_list_free_g_object_unref (GList* self);
void icon_list_control_add_next_files (IconListControl* self, const char* dirname, GList* files);
void icon_list_control_add_folder (IconListControl* self, const char* dirname, GCancellable* cancellable, GAsyncReadyCallback _callback_, gpointer _user_data_);
void icon_list_control_add_folder_finish (IconListControl* self, GAsyncResult* _res_);
static gboolean icon_list_control_add_folder_co (IconListControlAddFolderData* data);
GtkListStore* icon_list_control_get_iconlist_store (IconListControl* self);
static void icon_list_control_fill_icons_data_free (gpointer _data);
static void icon_list_control_fill_icons_ready (GObject* source_object, GAsyncResult* _res_, gpointer _user_data_);
void icon_list_control_fill_icons (IconListControl* self, GtkTreePath* path, GtkTreePath* end, GCancellable* cancellable, GAsyncReadyCallback _callback_, gpointer _user_data_);
void icon_list_control_fill_icons_finish (IconListControl* self, GAsyncResult* _res_);
static gboolean _icon_list_control_fill_icons_co_gsource_func (gpointer self);
static inline void _dynamic_set_location0 (GstElement* obj, const char* value);
static gboolean icon_list_control_fill_icons_co (IconListControlFillIconsData* data);
static inline GdkPixbuf* _dynamic_get_last_pixbuf1 (GstElement* obj);
void icon_list_control_on_error (IconListControl* self, GError* _error_, const char* debug);
void icon_list_control_on_eos (IconListControl* self);
IconListControlCol icon_list_control_get_text_column (void);
IconListControlCol icon_list_control_get_pixbuf_column (void);
gboolean icon_list_control_iter_is_valid (IconListControl* self, GtkTreeIter* iter);
gboolean icon_list_control_iter_is_filled (IconListControl* self, GtkTreeIter* iter);
char* icon_list_control_iter_get_file (IconListControl* self, GtkTreeIter* iter);
static void _icon_list_control_on_eos_media_control_eos_message (IconListControl* _sender, gpointer self);
static void _icon_list_control_on_error_media_control_error_message (IconListControl* _sender, GError* _error_, const char* debug, gpointer self);
static GObject * icon_list_control_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static void icon_list_control_finalize (GObject* obj);
static void icon_list_control_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void icon_list_control_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);
static int _vala_strcmp0 (const char * str1, const char * str2);




GType icon_list_control_col_get_type (void) {
	static GType icon_list_control_col_type_id = 0;
	if (G_UNLIKELY (icon_list_control_col_type_id == 0)) {
		static const GEnumValue values[] = {{ICON_LIST_CONTROL_COL_TEXT, "ICON_LIST_CONTROL_COL_TEXT", "text"}, {ICON_LIST_CONTROL_COL_FILE, "ICON_LIST_CONTROL_COL_FILE", "file"}, {ICON_LIST_CONTROL_COL_PIXBUF, "ICON_LIST_CONTROL_COL_PIXBUF", "pixbuf"}, {ICON_LIST_CONTROL_COL_VALID, "ICON_LIST_CONTROL_COL_VALID", "valid"}, {ICON_LIST_CONTROL_COL_FILLED, "ICON_LIST_CONTROL_COL_FILLED", "filled"}, {0, NULL, NULL}};
		icon_list_control_col_type_id = g_enum_register_static ("IconListControlCol", values);
	}
	return icon_list_control_col_type_id;
}


IconListControl* icon_list_control_construct (GType object_type, GtkListStore* model, GError** error) {
	GError * _inner_error_;
	IconListControl * self;
	g_return_val_if_fail (model != NULL, NULL);
	_inner_error_ = NULL;
	self = g_object_newv (object_type, 0, NULL);
	icon_list_control_set_iconlist_store (self, model);
	if (!icon_list_control_pixbufs_loaded) {
		icon_list_control_setup_icons (self, &_inner_error_);
		if (_inner_error_ != NULL) {
			g_propagate_error (error, _inner_error_);
			return NULL;
		}
		icon_list_control_pixbufs_loaded = TRUE;
	}
	icon_list_control_setup_elements (self, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return NULL;
	}
	return self;
}


IconListControl* icon_list_control_new (GtkListStore* model, GError** error) {
	return icon_list_control_construct (TYPE_ICON_LIST_CONTROL, model, error);
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


void icon_list_control_setup_icons (IconListControl* self, GError** error) {
	GError * _inner_error_;
	GtkIconTheme* icon_theme;
	GtkIconInfo* icon_info;
	GtkIconInfo* _tmp0_;
	GtkIconInfo* _tmp3_;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	icon_theme = _g_object_ref0 (gtk_icon_theme_get_default ());
	icon_info = NULL;
	icon_info = (_tmp0_ = gtk_icon_theme_lookup_icon (icon_theme, GTK_STOCK_MISSING_IMAGE, 96, GTK_ICON_LOOKUP_FORCE_SIZE), _gtk_icon_info_free0 (icon_info), _tmp0_);
	if (icon_info != NULL) {
		GdkPixbuf* _tmp1_;
		GdkPixbuf* _tmp2_;
		_tmp1_ = gtk_icon_info_load_icon (icon_info, &_inner_error_);
		if (_inner_error_ != NULL) {
			g_propagate_error (error, _inner_error_);
			_g_object_unref0 (icon_theme);
			_gtk_icon_info_free0 (icon_info);
			return;
		}
		self->missing_pixbuf = (_tmp2_ = _tmp1_, _g_object_unref0 (self->missing_pixbuf), _tmp2_);
	}
	icon_info = (_tmp3_ = gtk_icon_theme_lookup_icon (icon_theme, "image-loading", 96, GTK_ICON_LOOKUP_FORCE_SIZE), _gtk_icon_info_free0 (icon_info), _tmp3_);
	if (icon_info != NULL) {
		GdkPixbuf* _tmp4_;
		GdkPixbuf* _tmp5_;
		_tmp4_ = gtk_icon_info_load_icon (icon_info, &_inner_error_);
		if (_inner_error_ != NULL) {
			g_propagate_error (error, _inner_error_);
			_g_object_unref0 (icon_theme);
			_gtk_icon_info_free0 (icon_info);
			return;
		}
		icon_list_control_loading_pixbuf = (_tmp5_ = _tmp4_, _g_object_unref0 (icon_list_control_loading_pixbuf), _tmp5_);
	}
	_g_object_unref0 (icon_theme);
	_gtk_icon_info_free0 (icon_info);
}


void icon_list_control_setup_elements (IconListControl* self, GError** error) {
	GError * _inner_error_;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	icon_list_control_setup_pipeline (self, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
}


static void _icon_list_control_on_structure_media_control_structure_message (IconListControl* _sender, GstObject* src, const char* name, gpointer self) {
	icon_list_control_on_structure (self, src, name);
}


void icon_list_control_setup_pipeline (IconListControl* self, GError** error) {
	GError * _inner_error_;
	GstElement* _tmp0_;
	GstElement* _tmp1_;
	GstPipeline* icon_pipeline;
	GstElement* _tmp2_;
	GstElement* _tmp3_;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	_tmp0_ = gst_parse_launch (ICON_PIPELINE_DESC, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	icon_pipeline = (_tmp1_ = _tmp0_, GST_IS_PIPELINE (_tmp1_) ? ((GstPipeline*) _tmp1_) : NULL);
	gst_object_set_name ((GstObject*) icon_pipeline, "icon_pipeline");
	if ((self->filesrc = (_tmp2_ = gst_bin_get_by_name ((GstBin*) icon_pipeline, "filesrc"), _gst_object_unref0 (self->filesrc), _tmp2_)) == NULL) {
		_inner_error_ = g_error_new_literal (GST_CORE_ERROR, GST_CORE_ERROR_FAILED, "No element named filesrc in the icon pipeline");
		if (_inner_error_ != NULL) {
			g_propagate_error (error, _inner_error_);
			_gst_object_unref0 (icon_pipeline);
			return;
		}
	}
	if ((self->imagesink = (_tmp3_ = gst_bin_get_by_name ((GstBin*) icon_pipeline, "imagesink"), _gst_object_unref0 (self->imagesink), _tmp3_)) == NULL) {
		_inner_error_ = g_error_new_literal (GST_CORE_ERROR, GST_CORE_ERROR_FAILED, "No element named imagesink in the icon pipeline");
		if (_inner_error_ != NULL) {
			g_propagate_error (error, _inner_error_);
			_gst_object_unref0 (icon_pipeline);
			return;
		}
	}
	media_control_set_pipeline ((MediaControl*) self, (GstBin*) icon_pipeline);
	g_signal_connect_object ((MediaControl*) self, "structure-message", (GCallback) _icon_list_control_on_structure_media_control_structure_message, self, 0);
	_gst_object_unref0 (icon_pipeline);
}


static void icon_list_control_add_folder_data_free (gpointer _data) {
	IconListControlAddFolderData* data;
	data = _data;
	_g_free0 (data->dirname);
	_g_object_unref0 (data->cancellable);
	g_slice_free (IconListControlAddFolderData, data);
}


void icon_list_control_add_folder (IconListControl* self, const char* dirname, GCancellable* cancellable, GAsyncReadyCallback _callback_, gpointer _user_data_) {
	IconListControlAddFolderData* _data_;
	_data_ = g_slice_new0 (IconListControlAddFolderData);
	_data_->_async_result = g_simple_async_result_new (G_OBJECT (self), _callback_, _user_data_, icon_list_control_add_folder);
	g_simple_async_result_set_op_res_gpointer (_data_->_async_result, _data_, icon_list_control_add_folder_data_free);
	_data_->self = self;
	_data_->dirname = g_strdup (dirname);
	_data_->cancellable = _g_object_ref0 (cancellable);
	icon_list_control_add_folder_co (_data_);
}


void icon_list_control_add_folder_finish (IconListControl* self, GAsyncResult* _res_) {
	IconListControlAddFolderData* _data_;
	_data_ = g_simple_async_result_get_op_res_gpointer (G_SIMPLE_ASYNC_RESULT (_res_));
}


static void icon_list_control_add_folder_ready (GObject* source_object, GAsyncResult* _res_, gpointer _user_data_) {
	IconListControlAddFolderData* data;
	data = _user_data_;
	data->_res_ = _res_;
	icon_list_control_add_folder_co (data);
}


static void _g_list_free_g_object_unref (GList* self) {
	g_list_foreach (self, (GFunc) g_object_unref, NULL);
	g_list_free (self);
}


static gboolean icon_list_control_add_folder_co (IconListControlAddFolderData* data) {
	switch (data->_state_) {
		default:
		g_assert_not_reached ();
		case 0:
		{
			data->dir = g_file_new_for_path (data->dirname);
			{
				g_file_enumerate_children_async (data->dir, IMAGE_FILE_ATTRIBUTES, G_FILE_QUERY_INFO_NONE, G_PRIORITY_DEFAULT, data->cancellable, icon_list_control_add_folder_ready, data);
				data->_state_ = 1;
				return FALSE;
				case 1:
				data->file_etor = g_file_enumerate_children_finish (data->dir, data->_res_, &data->_inner_error_);
				if (data->_inner_error_ != NULL) {
					goto __catch1_g_error;
					goto __finally1;
				}
				while (TRUE) {
					if (!(!g_cancellable_is_cancelled (data->cancellable))) {
						break;
					}
					g_file_enumerator_next_files_async (data->file_etor, 5, G_PRIORITY_DEFAULT, data->cancellable, icon_list_control_add_folder_ready, data);
					data->_state_ = 2;
					return FALSE;
					case 2:
					data->next_files = g_file_enumerator_next_files_finish (data->file_etor, data->_res_, &data->_inner_error_);
					if (data->_inner_error_ != NULL) {
						_g_object_unref0 (data->file_etor);
						goto __catch1_g_error;
						goto __finally1;
					}
					if (data->next_files == NULL) {
						__g_list_free_g_object_unref0 (data->next_files);
						break;
					}
					icon_list_control_add_next_files (data->self, data->dirname, data->next_files);
					__g_list_free_g_object_unref0 (data->next_files);
				}
				_g_object_unref0 (data->file_etor);
			}
			goto __finally1;
			__catch1_g_error:
			{
				data->e1 = data->_inner_error_;
				data->_inner_error_ = NULL;
				{
					g_print ("%s", data->_tmp0_ = g_strconcat (data->e1->message, "\n", NULL));
					_g_free0 (data->_tmp0_);
					_g_error_free0 (data->e1);
				}
			}
			__finally1:
			{
				g_signal_emit_by_name (data->self, "files-added");
			}
			if (data->_inner_error_ != NULL) {
				_g_object_unref0 (data->dir);
				g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, data->_inner_error_->message, g_quark_to_string (data->_inner_error_->domain), data->_inner_error_->code);
				g_clear_error (&data->_inner_error_);
				return FALSE;
			}
			_g_object_unref0 (data->dir);
		}
		{
			if (data->_state_ == 0) {
				g_simple_async_result_complete_in_idle (data->_async_result);
			} else {
				g_simple_async_result_complete (data->_async_result);
			}
			g_object_unref (data->_async_result);
			return FALSE;
		}
	}
}


void icon_list_control_add_next_files (IconListControl* self, const char* dirname, GList* files) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (dirname != NULL);
	{
		GList* info_collection;
		GList* info_it;
		info_collection = files;
		for (info_it = info_collection; info_it != NULL; info_it = info_it->next) {
			GFileInfo* info;
			info = _g_object_ref0 ((GFileInfo*) info_it->data);
			{
				if (_vala_strcmp0 (g_file_info_get_content_type (info), "image/jpeg") == 0) {
					char* file;
					char* text;
					file = g_build_filename (dirname, g_file_info_get_name (info), NULL);
					text = g_strdup (g_file_info_get_display_name (info));
					gtk_list_store_insert_with_values (self->priv->_iconlist_store, NULL, -1, ICON_LIST_CONTROL_COL_TEXT, text, ICON_LIST_CONTROL_COL_FILE, file, ICON_LIST_CONTROL_COL_PIXBUF, icon_list_control_loading_pixbuf, -1, -1);
					_g_free0 (file);
					_g_free0 (text);
				}
				_g_object_unref0 (info);
			}
		}
	}
}


static void icon_list_control_fill_icons_data_free (gpointer _data) {
	IconListControlFillIconsData* data;
	data = _data;
	_gtk_tree_path_free0 (data->path);
	_gtk_tree_path_free0 (data->end);
	_g_object_unref0 (data->cancellable);
	g_slice_free (IconListControlFillIconsData, data);
}


static gpointer _gtk_tree_path_copy0 (gpointer self) {
	return self ? gtk_tree_path_copy (self) : NULL;
}


void icon_list_control_fill_icons (IconListControl* self, GtkTreePath* path, GtkTreePath* end, GCancellable* cancellable, GAsyncReadyCallback _callback_, gpointer _user_data_) {
	IconListControlFillIconsData* _data_;
	_data_ = g_slice_new0 (IconListControlFillIconsData);
	_data_->_async_result = g_simple_async_result_new (G_OBJECT (self), _callback_, _user_data_, icon_list_control_fill_icons);
	g_simple_async_result_set_op_res_gpointer (_data_->_async_result, _data_, icon_list_control_fill_icons_data_free);
	_data_->self = self;
	_data_->path = _gtk_tree_path_copy0 (path);
	_data_->end = _gtk_tree_path_copy0 (end);
	_data_->cancellable = _g_object_ref0 (cancellable);
	icon_list_control_fill_icons_co (_data_);
}


void icon_list_control_fill_icons_finish (IconListControl* self, GAsyncResult* _res_) {
	IconListControlFillIconsData* _data_;
	_data_ = g_simple_async_result_get_op_res_gpointer (G_SIMPLE_ASYNC_RESULT (_res_));
}


static void icon_list_control_fill_icons_ready (GObject* source_object, GAsyncResult* _res_, gpointer _user_data_) {
	IconListControlFillIconsData* data;
	data = _user_data_;
	data->_res_ = _res_;
	icon_list_control_fill_icons_co (data);
}


static gboolean _icon_list_control_fill_icons_co_gsource_func (gpointer self) {
	return icon_list_control_fill_icons_co (self);
}


static inline void _dynamic_set_location0 (GstElement* obj, const char* value) {
	g_object_set (obj, "location", value, NULL);
}


static gboolean icon_list_control_fill_icons_co (IconListControlFillIconsData* data) {
	switch (data->_state_) {
		default:
		g_assert_not_reached ();
		case 0:
		{
			data->self->continuation = (data->_tmp0_ = _icon_list_control_fill_icons_co_gsource_func, ((data->self->continuation_target_destroy_notify == NULL) ? NULL : data->self->continuation_target_destroy_notify (data->self->continuation_target), data->self->continuation = NULL, data->self->continuation_target = NULL, data->self->continuation_target_destroy_notify = NULL), data->self->continuation_target = data, data->self->continuation_target_destroy_notify = NULL, data->_tmp0_);
			gst_element_set_state ((GstElement*) ((MediaControl*) data->self)->pipeline, GST_STATE_READY);
			{
				data->_tmp1_ = TRUE;
				while (TRUE) {
					if (!data->_tmp1_) {
						if (gtk_tree_path_compare (data->path, data->end) > 0) {
							data->_tmp2_ = TRUE;
						} else {
							data->_tmp2_ = g_cancellable_is_cancelled (data->cancellable);
						}
						if (!(!data->_tmp2_)) {
							break;
						}
					}
					data->_tmp1_ = FALSE;
					gtk_tree_model_get_iter ((GtkTreeModel*) data->self->priv->_iconlist_store, &data->iter, data->path);
					gtk_tree_model_get ((GtkTreeModel*) data->self->priv->_iconlist_store, &data->iter, ICON_LIST_CONTROL_COL_FILE, &data->file, ICON_LIST_CONTROL_COL_FILLED, &data->filled, -1, -1);
					if (!data->filled) {
						data->self->continuation_error = (data->_tmp3_ = NULL, _g_error_free0 (data->self->continuation_error), data->_tmp3_);
						_dynamic_set_location0 (data->self->filesrc, data->file);
						gst_element_set_state ((GstElement*) ((MediaControl*) data->self)->pipeline, GST_STATE_PLAYING);
						data->_state_ = 3;
						return FALSE;
						case 3:
						;
						gst_element_set_state ((GstElement*) ((MediaControl*) data->self)->pipeline, GST_STATE_READY);
						if (data->self->continuation_error == NULL) {
							data->_tmp4_ = icon_list_control_last_pixbuf != NULL;
						} else {
							data->_tmp4_ = FALSE;
						}
						if (data->valid = data->_tmp4_) {
							data->pixbuf = (data->_tmp6_ = (data->_tmp5_ = icon_list_control_last_pixbuf, icon_list_control_last_pixbuf = NULL, data->_tmp5_), _g_object_unref0 (data->pixbuf), data->_tmp6_);
						} else {
							data->pixbuf = (data->_tmp7_ = _g_object_ref0 (data->self->missing_pixbuf), _g_object_unref0 (data->pixbuf), data->_tmp7_);
						}
						gtk_list_store_set (data->self->priv->_iconlist_store, &data->iter, ICON_LIST_CONTROL_COL_PIXBUF, data->pixbuf, ICON_LIST_CONTROL_COL_VALID, data->valid, -1, -1);
						_g_object_unref0 (data->pixbuf);
					}
					gtk_tree_path_next (data->path);
					_g_free0 (data->file);
				}
			}
			gst_element_set_state ((GstElement*) ((MediaControl*) data->self)->pipeline, GST_STATE_NULL);
			g_signal_emit_by_name (data->self, "icons-filled");
		}
		{
			if (data->_state_ == 0) {
				g_simple_async_result_complete_in_idle (data->_async_result);
			} else {
				g_simple_async_result_complete (data->_async_result);
			}
			g_object_unref (data->_async_result);
			return FALSE;
		}
	}
}


static inline GdkPixbuf* _dynamic_get_last_pixbuf1 (GstElement* obj) {
	GdkPixbuf* result;
	g_object_get (obj, "last-pixbuf", &result, NULL);
	return result;
}


void icon_list_control_on_structure (IconListControl* self, GstObject* src, const char* name) {
	gboolean _tmp0_ = FALSE;
	g_return_if_fail (self != NULL);
	g_return_if_fail (src != NULL);
	g_return_if_fail (name != NULL);
	if (src == GST_OBJECT (self->imagesink)) {
		_tmp0_ = _vala_strcmp0 (name, "pixbuf") == 0;
	} else {
		_tmp0_ = FALSE;
	}
	if (_tmp0_) {
		GdkPixbuf* _tmp1_;
		icon_list_control_last_pixbuf = (_tmp1_ = _dynamic_get_last_pixbuf1 (self->imagesink), _g_object_unref0 (icon_list_control_last_pixbuf), _tmp1_);
	}
}


static gpointer _g_error_copy0 (gpointer self) {
	return self ? g_error_copy (self) : NULL;
}


void icon_list_control_on_error (IconListControl* self, GError* _error_, const char* debug) {
	GError* _tmp0_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (debug != NULL);
	self->continuation_error = (_tmp0_ = _g_error_copy0 (_error_), _g_error_free0 (self->continuation_error), _tmp0_);
	g_idle_add_full (G_PRIORITY_DEFAULT_IDLE, self->continuation, self->continuation_target, NULL);
}


void icon_list_control_on_eos (IconListControl* self) {
	g_return_if_fail (self != NULL);
	g_idle_add_full (G_PRIORITY_DEFAULT_IDLE, self->continuation, self->continuation_target, NULL);
}


IconListControlCol icon_list_control_get_text_column (void) {
	IconListControlCol result;
	result = ICON_LIST_CONTROL_COL_TEXT;
	return result;
}


IconListControlCol icon_list_control_get_pixbuf_column (void) {
	IconListControlCol result;
	result = ICON_LIST_CONTROL_COL_PIXBUF;
	return result;
}


gboolean icon_list_control_iter_is_valid (IconListControl* self, GtkTreeIter* iter) {
	gboolean result;
	gboolean valid = FALSE;
	g_return_val_if_fail (self != NULL, FALSE);
	gtk_tree_model_get ((GtkTreeModel*) self->priv->_iconlist_store, iter, ICON_LIST_CONTROL_COL_VALID, &valid, -1, -1);
	result = valid;
	return result;
}


gboolean icon_list_control_iter_is_filled (IconListControl* self, GtkTreeIter* iter) {
	gboolean result;
	gboolean filled = FALSE;
	g_return_val_if_fail (self != NULL, FALSE);
	gtk_tree_model_get ((GtkTreeModel*) self->priv->_iconlist_store, iter, ICON_LIST_CONTROL_COL_FILLED, &filled, -1, -1);
	result = filled;
	return result;
}


char* icon_list_control_iter_get_file (IconListControl* self, GtkTreeIter* iter) {
	char* result;
	char* file;
	g_return_val_if_fail (self != NULL, NULL);
	file = NULL;
	gtk_tree_model_get ((GtkTreeModel*) self->priv->_iconlist_store, iter, ICON_LIST_CONTROL_COL_FILE, &file, -1, -1);
	result = file;
	return result;
}


GtkListStore* icon_list_control_get_iconlist_store (IconListControl* self) {
	GtkListStore* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_iconlist_store;
	return result;
}


void icon_list_control_set_iconlist_store (IconListControl* self, GtkListStore* value) {
	g_return_if_fail (self != NULL);
	self->priv->_iconlist_store = value;
	g_object_notify ((GObject *) self, "iconlist-store");
}


static void _icon_list_control_on_eos_media_control_eos_message (IconListControl* _sender, gpointer self) {
	icon_list_control_on_eos (self);
}


static void _icon_list_control_on_error_media_control_error_message (IconListControl* _sender, GError* _error_, const char* debug, gpointer self) {
	icon_list_control_on_error (self, _error_, debug);
}


static GObject * icon_list_control_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GObjectClass * parent_class;
	IconListControl * self;
	parent_class = G_OBJECT_CLASS (icon_list_control_parent_class);
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = ICON_LIST_CONTROL (obj);
	{
		g_signal_connect_object ((MediaControl*) self, "eos-message", (GCallback) _icon_list_control_on_eos_media_control_eos_message, self, 0);
		g_signal_connect_object ((MediaControl*) self, "error-message", (GCallback) _icon_list_control_on_error_media_control_error_message, self, 0);
	}
	return obj;
}


static void icon_list_control_class_init (IconListControlClass * klass) {
	icon_list_control_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (IconListControlPrivate));
	G_OBJECT_CLASS (klass)->get_property = icon_list_control_get_property;
	G_OBJECT_CLASS (klass)->set_property = icon_list_control_set_property;
	G_OBJECT_CLASS (klass)->constructor = icon_list_control_constructor;
	G_OBJECT_CLASS (klass)->finalize = icon_list_control_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), ICON_LIST_CONTROL_ICONLIST_STORE, g_param_spec_object ("iconlist-store", "iconlist-store", "iconlist-store", GTK_TYPE_LIST_STORE, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_signal_new ("files_added", TYPE_ICON_LIST_CONTROL, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);
	g_signal_new ("icons_filled", TYPE_ICON_LIST_CONTROL, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);
	icon_list_control_pixbuf_q = g_quark_from_string ("pixbuf");
}


static void icon_list_control_instance_init (IconListControl * self) {
	self->priv = ICON_LIST_CONTROL_GET_PRIVATE (self);
}


static void icon_list_control_finalize (GObject* obj) {
	IconListControl * self;
	self = ICON_LIST_CONTROL (obj);
	_gst_object_unref0 (self->filesrc);
	_gst_object_unref0 (self->imagesink);
	_g_object_unref0 (self->missing_pixbuf);
	(self->continuation_target_destroy_notify == NULL) ? NULL : self->continuation_target_destroy_notify (self->continuation_target);
	self->continuation = NULL;
	self->continuation_target = NULL;
	self->continuation_target_destroy_notify = NULL;
	_g_error_free0 (self->continuation_error);
	G_OBJECT_CLASS (icon_list_control_parent_class)->finalize (obj);
}


GType icon_list_control_get_type (void) {
	static GType icon_list_control_type_id = 0;
	if (icon_list_control_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (IconListControlClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) icon_list_control_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (IconListControl), 0, (GInstanceInitFunc) icon_list_control_instance_init, NULL };
		icon_list_control_type_id = g_type_register_static (TYPE_MEDIA_CONTROL, "IconListControl", &g_define_type_info, 0);
	}
	return icon_list_control_type_id;
}


static void icon_list_control_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	IconListControl * self;
	self = ICON_LIST_CONTROL (object);
	switch (property_id) {
		case ICON_LIST_CONTROL_ICONLIST_STORE:
		g_value_set_object (value, icon_list_control_get_iconlist_store (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void icon_list_control_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	IconListControl * self;
	self = ICON_LIST_CONTROL (object);
	switch (property_id) {
		case ICON_LIST_CONTROL_ICONLIST_STORE:
		icon_list_control_set_iconlist_store (self, g_value_get_object (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static int _vala_strcmp0 (const char * str1, const char * str2) {
	if (str1 == NULL) {
		return -(str1 != str2);
	}
	if (str2 == NULL) {
		return str1 != str2;
	}
	return strcmp (str1, str2);
}




