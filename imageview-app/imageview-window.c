/* imageview-window.c generated by valac, the Vala compiler
 * generated from imageview-window.gs, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <gio/gio.h>
#include <gdk-pixbuf/gdk-pixdata.h>
#include <gst/gst.h>


#define TYPE_MEDIA_WINDOW (media_window_get_type ())
#define MEDIA_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_MEDIA_WINDOW, MediaWindow))
#define MEDIA_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_MEDIA_WINDOW, MediaWindowClass))
#define IS_MEDIA_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_MEDIA_WINDOW))
#define IS_MEDIA_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_MEDIA_WINDOW))
#define MEDIA_WINDOW_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_MEDIA_WINDOW, MediaWindowClass))

typedef struct _MediaWindow MediaWindow;
typedef struct _MediaWindowClass MediaWindowClass;
typedef struct _MediaWindowPrivate MediaWindowPrivate;

#define TYPE_IMAGE_VIEW_WINDOW (image_view_window_get_type ())
#define IMAGE_VIEW_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_IMAGE_VIEW_WINDOW, ImageViewWindow))
#define IMAGE_VIEW_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_IMAGE_VIEW_WINDOW, ImageViewWindowClass))
#define IS_IMAGE_VIEW_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_IMAGE_VIEW_WINDOW))
#define IS_IMAGE_VIEW_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_IMAGE_VIEW_WINDOW))
#define IMAGE_VIEW_WINDOW_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_IMAGE_VIEW_WINDOW, ImageViewWindowClass))

typedef struct _ImageViewWindow ImageViewWindow;
typedef struct _ImageViewWindowClass ImageViewWindowClass;
typedef struct _ImageViewWindowPrivate ImageViewWindowPrivate;

#define TYPE_VIDEO_AREA (video_area_get_type ())
#define VIDEO_AREA(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_VIDEO_AREA, VideoArea))
#define VIDEO_AREA_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_VIDEO_AREA, VideoAreaClass))
#define IS_VIDEO_AREA(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_VIDEO_AREA))
#define IS_VIDEO_AREA_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_VIDEO_AREA))
#define VIDEO_AREA_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_VIDEO_AREA, VideoAreaClass))

typedef struct _VideoArea VideoArea;
typedef struct _VideoAreaClass VideoAreaClass;

#define TYPE_MEDIA_CONTROL (media_control_get_type ())
#define MEDIA_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_MEDIA_CONTROL, MediaControl))
#define MEDIA_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_MEDIA_CONTROL, MediaControlClass))
#define IS_MEDIA_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_MEDIA_CONTROL))
#define IS_MEDIA_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_MEDIA_CONTROL))
#define MEDIA_CONTROL_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_MEDIA_CONTROL, MediaControlClass))

typedef struct _MediaControl MediaControl;
typedef struct _MediaControlClass MediaControlClass;

#define TYPE_ICON_LIST_CONTROL (icon_list_control_get_type ())
#define ICON_LIST_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_ICON_LIST_CONTROL, IconListControl))
#define ICON_LIST_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_ICON_LIST_CONTROL, IconListControlClass))
#define IS_ICON_LIST_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_ICON_LIST_CONTROL))
#define IS_ICON_LIST_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_ICON_LIST_CONTROL))
#define ICON_LIST_CONTROL_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_ICON_LIST_CONTROL, IconListControlClass))

typedef struct _IconListControl IconListControl;
typedef struct _IconListControlClass IconListControlClass;

#define TYPE_IMAGE_CONTROL (image_control_get_type ())
#define IMAGE_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_IMAGE_CONTROL, ImageControl))
#define IMAGE_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_IMAGE_CONTROL, ImageControlClass))
#define IS_IMAGE_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_IMAGE_CONTROL))
#define IS_IMAGE_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_IMAGE_CONTROL))
#define IMAGE_CONTROL_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_IMAGE_CONTROL, ImageControlClass))

typedef struct _ImageControl ImageControl;
typedef struct _ImageControlClass ImageControlClass;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))

#define ICON_LIST_CONTROL_TYPE_COL (icon_list_control_col_get_type ())

#define MEDIA_WINDOW_TYPE_TAB (media_window_tab_get_type ())
#define _gtk_tree_path_free0(var) ((var == NULL) ? NULL : (var = (gtk_tree_path_free (var), NULL)))
typedef struct _ImageViewWindowSlideshowData ImageViewWindowSlideshowData;

struct _MediaWindow {
	GtkWindow parent_instance;
	MediaWindowPrivate * priv;
	GtkNotebook* notebook;
	GtkToolbar* toolbar;
	GtkVBox* main_box;
};

struct _MediaWindowClass {
	GtkWindowClass parent_class;
};

struct _ImageViewWindow {
	MediaWindow parent_instance;
	ImageViewWindowPrivate * priv;
	GtkFileChooserButton* chooser_button;
	GtkIconView* icon_view;
	VideoArea* video_area;
	GtkListStore* iconlist_store;
	IconListControl* iconlist_control;
	ImageControl* image_control;
	char* current_folder;
	GtkToolButton* image_button;
	GtkToolButton* slideshow_button;
	guint slideshow_timeout;
	GSourceFunc slideshow_continuation;
	gpointer slideshow_continuation_target;
	GDestroyNotify slideshow_continuation_target_destroy_notify;
	GCancellable* slideshow_cancellable;
	gboolean is_filling_icons;
	GSourceFunc fill_icons_continuation;
	gpointer fill_icons_continuation_target;
	GDestroyNotify fill_icons_continuation_target_destroy_notify;
	GCancellable* fill_icons_cancellable;
};

struct _ImageViewWindowClass {
	MediaWindowClass parent_class;
};

typedef enum  {
	ICON_LIST_CONTROL_COL_TEXT,
	ICON_LIST_CONTROL_COL_FILE,
	ICON_LIST_CONTROL_COL_PIXBUF,
	ICON_LIST_CONTROL_COL_VALID,
	ICON_LIST_CONTROL_COL_FILLED,
	ICON_LIST_CONTROL_COL_WIDTH,
	ICON_LIST_CONTROL_COL_HEIGHT
} IconListControlCol;

typedef enum  {
	MEDIA_WINDOW_TAB_LIST,
	MEDIA_WINDOW_TAB_VIDEO
} MediaWindowTab;

struct _ImageViewWindowSlideshowData {
	int _state_;
	GAsyncResult* _res_;
	GSimpleAsyncResult* _async_result;
	ImageViewWindow* self;
	GtkTreeIter iter;
	gboolean _tmp0_;
	GSourceFunc _tmp1_;
	gboolean _tmp2_;
	gboolean _tmp3_;
	GtkTreePath* path;
	GSourceFunc _tmp4_;
	GCancellable* _tmp5_;
};


static gpointer image_view_window_parent_class = NULL;

#define TITLE "ImageViewApp"
GType media_window_get_type (void);
GType image_view_window_get_type (void);
GType video_area_get_type (void);
GType media_control_get_type (void);
GType icon_list_control_get_type (void);
GType image_control_get_type (void);
enum  {
	IMAGE_VIEW_WINDOW_DUMMY_PROPERTY
};
void image_view_window_setup_controls (ImageViewWindow* self, GError** error);
ImageViewWindow* image_view_window_new (GError** error);
ImageViewWindow* image_view_window_construct (GType object_type, GError** error);
void image_view_window_setup_model (ImageViewWindow* self);
IconListControl* icon_list_control_new (GtkListStore* model, GError** error);
IconListControl* icon_list_control_construct (GType object_type, GtkListStore* model, GError** error);
void image_view_window_on_iconlist_files_added (ImageViewWindow* self);
static void _image_view_window_on_iconlist_files_added_icon_list_control_files_added (IconListControl* _sender, gpointer self);
void image_view_window_on_iconlist_icons_filled (ImageViewWindow* self);
static void _image_view_window_on_iconlist_icons_filled_icon_list_control_icons_filled (IconListControl* _sender, gpointer self);
ImageControl* image_control_new (GError** error);
ImageControl* image_control_construct (GType object_type, GError** error);
void image_view_window_on_image_control_eos (ImageViewWindow* self);
static void _image_view_window_on_image_control_eos_media_control_eos_message (ImageControl* _sender, GstObject* src, gpointer self);
void video_area_set_control (VideoArea* self, MediaControl* control);
void image_view_window_setup_toolbar (ImageViewWindow* self);
void image_view_window_setup_notebook (ImageViewWindow* self);
void image_view_window_setup_widgets (ImageViewWindow* self);
GtkBox* image_view_window_new_iconlist_box (ImageViewWindow* self);
GtkBox* image_view_window_new_video_box (ImageViewWindow* self);
void image_view_window_do_fill_visible_icons (ImageViewWindow* self);
static void _image_view_window_do_fill_visible_icons_gtk_adjustment_value_changed (GtkAdjustment* _sender, gpointer self);
static void _image_view_window_do_fill_visible_icons_gtk_widget_size_request (GtkIconView* _sender, GtkRequisition* requisition, gpointer self);
GType icon_list_control_col_get_type (void);
IconListControlCol icon_list_control_get_text_column (void);
IconListControlCol icon_list_control_get_pixbuf_column (void);
void image_view_window_on_icon_activated (ImageViewWindow* self, GtkTreePath* path);
static void _image_view_window_on_icon_activated_gtk_icon_view_item_activated (GtkIconView* _sender, GtkTreePath* path, gpointer self);
gboolean icon_list_control_iter_is_valid (IconListControl* self, GtkTreeIter* iter);
void icon_list_control_iter_get_size (IconListControl* self, GtkTreeIter* iter, gint* width, gint* height);
char* icon_list_control_iter_get_file (IconListControl* self, GtkTreeIter* iter);
void image_control_set_location (ImageControl* self, const char* value);
GstStateChangeReturn media_control_set_state (MediaControl* self, GstState state);
VideoArea* video_area_new (void);
VideoArea* video_area_construct (GType object_type);
void image_view_window_on_chooser_folder_changed (ImageViewWindow* self);
static void _image_view_window_on_chooser_folder_changed_gtk_file_chooser_current_folder_changed (GtkFileChooserButton* _sender, gpointer self);
void media_window_toolbar_add_expander (MediaWindow* self);
void image_view_window_on_open_close (ImageViewWindow* self);
static void _image_view_window_on_open_close_gtk_tool_button_clicked (GtkToolButton* _sender, gpointer self);
void image_view_window_on_slideshow (ImageViewWindow* self);
static void _image_view_window_on_slideshow_gtk_tool_button_clicked (GtkToolButton* _sender, gpointer self);
void media_window_toolbar_add_quit_button (MediaWindow* self);
GType media_window_tab_get_type (void);
void image_view_window_open (ImageViewWindow* self);
void image_view_window_close (ImageViewWindow* self);
gboolean image_view_window_get_and_select_iter (ImageViewWindow* self, GtkTreeIter* iter);
void image_view_window_start_slideshow (ImageViewWindow* self);
void image_view_window_stop_slideshow (ImageViewWindow* self);
void image_view_window_slideshow (ImageViewWindow* self, GAsyncReadyCallback _callback_, gpointer _user_data_);
void image_view_window_slideshow_finish (ImageViewWindow* self, GAsyncResult* _res_);
static void image_view_window_slideshow_data_free (gpointer _data);
static void image_view_window_slideshow_ready (GObject* source_object, GAsyncResult* _res_, gpointer _user_data_);
static gboolean _image_view_window_slideshow_co_gsource_func (gpointer self);
static gboolean image_view_window_slideshow_co (ImageViewWindowSlideshowData* data);
void image_view_window_change_folder (ImageViewWindow* self);
void icon_list_control_add_folder (IconListControl* self, const char* dirname, GCancellable* cancellable, GAsyncReadyCallback _callback_, gpointer _user_data_);
void icon_list_control_add_folder_finish (IconListControl* self, GAsyncResult* _res_);
gboolean image_view_window_retry_change_folder (ImageViewWindow* self);
static gboolean _image_view_window_retry_change_folder_gsource_func (gpointer self);
gboolean image_view_window_fill_visible_icons (ImageViewWindow* self);
static gboolean _image_view_window_fill_visible_icons_gsource_func (gpointer self);
gboolean image_view_window_retry_do_fill_visible_icons (ImageViewWindow* self);
static gboolean _image_view_window_retry_do_fill_visible_icons_gsource_func (gpointer self);
void icon_list_control_fill_icons (IconListControl* self, GtkTreePath* path, GtkTreePath* end, GCancellable* cancellable, GAsyncReadyCallback _callback_, gpointer _user_data_);
void icon_list_control_fill_icons_finish (IconListControl* self, GAsyncResult* _res_);
static GObject * image_view_window_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static void image_view_window_finalize (GObject* obj);
static int _vala_strcmp0 (const char * str1, const char * str2);



ImageViewWindow* image_view_window_construct (GType object_type, GError** error) {
	GError * _inner_error_;
	ImageViewWindow * self;
	_inner_error_ = NULL;
	self = g_object_newv (object_type, 0, NULL);
	image_view_window_setup_controls (self, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return NULL;
	}
	return self;
}


ImageViewWindow* image_view_window_new (GError** error) {
	return image_view_window_construct (TYPE_IMAGE_VIEW_WINDOW, error);
}


void image_view_window_setup_model (ImageViewWindow* self) {
	GType s;
	GType p;
	GType b;
	GType i;
	GtkListStore* _tmp0_;
	g_return_if_fail (self != NULL);
	s = G_TYPE_STRING;
	p = GDK_TYPE_PIXBUF;
	b = G_TYPE_BOOLEAN;
	i = G_TYPE_INT;
	self->iconlist_store = (_tmp0_ = gtk_list_store_new (7, s, s, p, b, b, i, i, NULL), _g_object_unref0 (self->iconlist_store), _tmp0_);
}


static void _image_view_window_on_iconlist_files_added_icon_list_control_files_added (IconListControl* _sender, gpointer self) {
	image_view_window_on_iconlist_files_added (self);
}


static void _image_view_window_on_iconlist_icons_filled_icon_list_control_icons_filled (IconListControl* _sender, gpointer self) {
	image_view_window_on_iconlist_icons_filled (self);
}


static void _image_view_window_on_image_control_eos_media_control_eos_message (ImageControl* _sender, GstObject* src, gpointer self) {
	image_view_window_on_image_control_eos (self);
}


void image_view_window_setup_controls (ImageViewWindow* self, GError** error) {
	GError * _inner_error_;
	IconListControl* _tmp0_;
	IconListControl* _tmp1_;
	ImageControl* _tmp2_;
	ImageControl* _tmp3_;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	_tmp0_ = icon_list_control_new (self->iconlist_store, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	self->iconlist_control = (_tmp1_ = _tmp0_, _g_object_unref0 (self->iconlist_control), _tmp1_);
	g_signal_connect_object (self->iconlist_control, "files-added", (GCallback) _image_view_window_on_iconlist_files_added_icon_list_control_files_added, self, 0);
	g_signal_connect_object (self->iconlist_control, "icons-filled", (GCallback) _image_view_window_on_iconlist_icons_filled_icon_list_control_icons_filled, self, 0);
	_tmp2_ = image_control_new (&_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	self->image_control = (_tmp3_ = _tmp2_, _g_object_unref0 (self->image_control), _tmp3_);
	g_signal_connect_object ((MediaControl*) self->image_control, "eos-message", (GCallback) _image_view_window_on_image_control_eos_media_control_eos_message, self, 0);
	video_area_set_control (self->video_area, (MediaControl*) self->image_control);
}


void image_view_window_setup_widgets (ImageViewWindow* self) {
	g_return_if_fail (self != NULL);
	gtk_window_set_title ((GtkWindow*) self, TITLE);
	image_view_window_setup_toolbar (self);
	image_view_window_setup_notebook (self);
	gtk_widget_realize ((GtkWidget*) self->video_area);
	gtk_widget_show_all ((GtkWidget*) ((MediaWindow*) self)->main_box);
}


void image_view_window_setup_notebook (ImageViewWindow* self) {
	GtkLabel* _tmp1_;
	GtkBox* _tmp0_;
	GtkLabel* _tmp3_;
	GtkBox* _tmp2_;
	g_return_if_fail (self != NULL);
	gtk_notebook_append_page (((MediaWindow*) self)->notebook, (GtkWidget*) (_tmp0_ = image_view_window_new_iconlist_box (self)), (GtkWidget*) (_tmp1_ = g_object_ref_sink ((GtkLabel*) gtk_label_new ("List"))));
	_g_object_unref0 (_tmp1_);
	_g_object_unref0 (_tmp0_);
	gtk_notebook_append_page (((MediaWindow*) self)->notebook, (GtkWidget*) (_tmp2_ = image_view_window_new_video_box (self)), (GtkWidget*) (_tmp3_ = g_object_ref_sink ((GtkLabel*) gtk_label_new ("Video"))));
	_g_object_unref0 (_tmp3_);
	_g_object_unref0 (_tmp2_);
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


static void _image_view_window_do_fill_visible_icons_gtk_adjustment_value_changed (GtkAdjustment* _sender, gpointer self) {
	image_view_window_do_fill_visible_icons (self);
}


static void _image_view_window_do_fill_visible_icons_gtk_widget_size_request (GtkIconView* _sender, GtkRequisition* requisition, gpointer self) {
	image_view_window_do_fill_visible_icons (self);
}


static void _image_view_window_on_icon_activated_gtk_icon_view_item_activated (GtkIconView* _sender, GtkTreePath* path, gpointer self) {
	image_view_window_on_icon_activated (self, path);
}


GtkBox* image_view_window_new_iconlist_box (ImageViewWindow* self) {
	GtkBox* result;
	GtkVBox* box;
	GtkScrolledWindow* scrolled_window;
	GtkAdjustment* adjustment;
	GtkAdjustment* _tmp0_;
	GtkAdjustment* _tmp1_;
	GtkIconView* _tmp2_;
	g_return_val_if_fail (self != NULL, NULL);
	box = g_object_ref_sink ((GtkVBox*) gtk_vbox_new (FALSE, 0));
	scrolled_window = g_object_ref_sink ((GtkScrolledWindow*) gtk_scrolled_window_new (NULL, NULL));
	gtk_box_pack_start ((GtkBox*) box, (GtkWidget*) scrolled_window, TRUE, TRUE, (guint) 0);
	gtk_scrolled_window_set_policy (scrolled_window, GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	adjustment = NULL;
	adjustment = (_tmp0_ = _g_object_ref0 (gtk_scrolled_window_get_vadjustment (scrolled_window)), _g_object_unref0 (adjustment), _tmp0_);
	g_signal_connect_object (adjustment, "value-changed", (GCallback) _image_view_window_do_fill_visible_icons_gtk_adjustment_value_changed, self, 0);
	adjustment = (_tmp1_ = _g_object_ref0 (gtk_scrolled_window_get_hadjustment (scrolled_window)), _g_object_unref0 (adjustment), _tmp1_);
	g_signal_connect_object (adjustment, "value-changed", (GCallback) _image_view_window_do_fill_visible_icons_gtk_adjustment_value_changed, self, 0);
	self->icon_view = (_tmp2_ = g_object_ref_sink ((GtkIconView*) gtk_icon_view_new ()), _g_object_unref0 (self->icon_view), _tmp2_);
	gtk_container_add ((GtkContainer*) scrolled_window, (GtkWidget*) self->icon_view);
	g_signal_connect_object ((GtkWidget*) self->icon_view, "size-request", (GCallback) _image_view_window_do_fill_visible_icons_gtk_widget_size_request, self, 0);
	gtk_icon_view_set_selection_mode (self->icon_view, GTK_SELECTION_BROWSE);
	gtk_icon_view_set_model (self->icon_view, (GtkTreeModel*) self->iconlist_store);
	gtk_icon_view_set_text_column (self->icon_view, (gint) icon_list_control_get_text_column ());
	gtk_icon_view_set_pixbuf_column (self->icon_view, (gint) icon_list_control_get_pixbuf_column ());
	gtk_icon_view_set_row_spacing (self->icon_view, 0);
	gtk_icon_view_set_column_spacing (self->icon_view, 0);
	gtk_icon_view_set_spacing (self->icon_view, 0);
	gtk_icon_view_set_margin (self->icon_view, 0);
	g_signal_connect_object (self->icon_view, "item-activated", (GCallback) _image_view_window_on_icon_activated_gtk_icon_view_item_activated, self, 0);
	result = (GtkBox*) box;
	_g_object_unref0 (scrolled_window);
	_g_object_unref0 (adjustment);
	return result;
}


void image_view_window_on_icon_activated (ImageViewWindow* self, GtkTreePath* path) {
	GtkTreeIter iter = {0};
	g_return_if_fail (self != NULL);
	g_return_if_fail (path != NULL);
	gtk_tree_model_get_iter ((GtkTreeModel*) self->iconlist_store, &iter, path);
	if (icon_list_control_iter_is_valid (self->iconlist_control, &iter)) {
		gint width = 0;
		gint height = 0;
		char* file;
		icon_list_control_iter_get_size (self->iconlist_control, &iter, &width, &height);
		gtk_widget_set_size_request ((GtkWidget*) self->video_area, width, height);
		file = icon_list_control_iter_get_file (self->iconlist_control, &iter);
		image_control_set_location (self->image_control, file);
		media_control_set_state ((MediaControl*) self->image_control, GST_STATE_PLAYING);
		gtk_tool_button_set_stock_id (self->image_button, GTK_STOCK_CLOSE);
		_g_free0 (file);
	}
}


GtkBox* image_view_window_new_video_box (ImageViewWindow* self) {
	GtkBox* result;
	GtkVBox* box;
	GtkScrolledWindow* scrolled_window;
	VideoArea* _tmp0_;
	g_return_val_if_fail (self != NULL, NULL);
	box = g_object_ref_sink ((GtkVBox*) gtk_vbox_new (FALSE, 0));
	scrolled_window = g_object_ref_sink ((GtkScrolledWindow*) gtk_scrolled_window_new (NULL, NULL));
	gtk_scrolled_window_set_policy (scrolled_window, GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start ((GtkBox*) box, (GtkWidget*) scrolled_window, TRUE, TRUE, (guint) 0);
	self->video_area = (_tmp0_ = g_object_ref_sink (video_area_new ()), _g_object_unref0 (self->video_area), _tmp0_);
	gtk_scrolled_window_add_with_viewport (scrolled_window, (GtkWidget*) self->video_area);
	result = (GtkBox*) box;
	_g_object_unref0 (scrolled_window);
	return result;
}


static void _image_view_window_on_chooser_folder_changed_gtk_file_chooser_current_folder_changed (GtkFileChooserButton* _sender, gpointer self) {
	image_view_window_on_chooser_folder_changed (self);
}


static void _image_view_window_on_open_close_gtk_tool_button_clicked (GtkToolButton* _sender, gpointer self) {
	image_view_window_on_open_close (self);
}


static void _image_view_window_on_slideshow_gtk_tool_button_clicked (GtkToolButton* _sender, gpointer self) {
	image_view_window_on_slideshow (self);
}


void image_view_window_setup_toolbar (ImageViewWindow* self) {
	GtkToolItem* chooser_item;
	GtkFileChooserButton* _tmp0_;
	GtkToolButton* _tmp1_;
	GtkToolButton* _tmp2_;
	g_return_if_fail (self != NULL);
	chooser_item = g_object_ref_sink (gtk_tool_item_new ());
	gtk_tool_item_set_expand (chooser_item, TRUE);
	gtk_container_add ((GtkContainer*) ((MediaWindow*) self)->toolbar, (GtkWidget*) chooser_item);
	self->chooser_button = (_tmp0_ = g_object_ref_sink ((GtkFileChooserButton*) gtk_file_chooser_button_new ("Select folder", GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER)), _g_object_unref0 (self->chooser_button), _tmp0_);
	gtk_container_add ((GtkContainer*) chooser_item, (GtkWidget*) self->chooser_button);
	gtk_file_chooser_set_create_folders ((GtkFileChooser*) self->chooser_button, FALSE);
	g_signal_connect_object ((GtkFileChooser*) self->chooser_button, "current-folder-changed", (GCallback) _image_view_window_on_chooser_folder_changed_gtk_file_chooser_current_folder_changed, self, 0);
	media_window_toolbar_add_expander ((MediaWindow*) self);
	self->image_button = (_tmp1_ = g_object_ref_sink ((GtkToolButton*) gtk_tool_button_new_from_stock (GTK_STOCK_ZOOM_100)), _g_object_unref0 (self->image_button), _tmp1_);
	gtk_container_add ((GtkContainer*) ((MediaWindow*) self)->toolbar, (GtkWidget*) self->image_button);
	g_signal_connect_object (self->image_button, "clicked", (GCallback) _image_view_window_on_open_close_gtk_tool_button_clicked, self, 0);
	media_window_toolbar_add_expander ((MediaWindow*) self);
	self->slideshow_button = (_tmp2_ = g_object_ref_sink ((GtkToolButton*) gtk_tool_button_new_from_stock (GTK_STOCK_MEDIA_PLAY)), _g_object_unref0 (self->slideshow_button), _tmp2_);
	gtk_container_add ((GtkContainer*) ((MediaWindow*) self)->toolbar, (GtkWidget*) self->slideshow_button);
	g_signal_connect_object (self->slideshow_button, "clicked", (GCallback) _image_view_window_on_slideshow_gtk_tool_button_clicked, self, 0);
	media_window_toolbar_add_quit_button ((MediaWindow*) self);
	_g_object_unref0 (chooser_item);
}


void image_view_window_on_open_close (ImageViewWindow* self) {
	g_return_if_fail (self != NULL);
	if (gtk_notebook_get_current_page (((MediaWindow*) self)->notebook) == MEDIA_WINDOW_TAB_LIST) {
		image_view_window_open (self);
	} else {
		image_view_window_close (self);
	}
}


void image_view_window_open (ImageViewWindow* self) {
	GtkTreeIter iter = {0};
	g_return_if_fail (self != NULL);
	if (image_view_window_get_and_select_iter (self, &iter)) {
		GtkTreePath* _tmp0_;
		gtk_icon_view_item_activated (self->icon_view, _tmp0_ = gtk_tree_model_get_path ((GtkTreeModel*) self->iconlist_store, &iter));
		_gtk_tree_path_free0 (_tmp0_);
	}
}


void image_view_window_close (ImageViewWindow* self) {
	g_return_if_fail (self != NULL);
	gtk_notebook_set_current_page (((MediaWindow*) self)->notebook, (gint) MEDIA_WINDOW_TAB_LIST);
	gtk_tool_button_set_stock_id (self->image_button, GTK_STOCK_ZOOM_100);
	gtk_tool_button_set_stock_id (self->slideshow_button, GTK_STOCK_MEDIA_PLAY);
}


void image_view_window_on_slideshow (ImageViewWindow* self) {
	GtkTreeIter iter = {0};
	g_return_if_fail (self != NULL);
	if (!gtk_tree_model_get_iter_first ((GtkTreeModel*) self->iconlist_store, &iter)) {
		return;
	}
	if (self->slideshow_continuation == NULL) {
		image_view_window_start_slideshow (self);
	} else {
		image_view_window_stop_slideshow (self);
	}
}


void image_view_window_start_slideshow (ImageViewWindow* self) {
	GCancellable* _tmp0_;
	g_return_if_fail (self != NULL);
	gtk_tool_button_set_stock_id (self->slideshow_button, GTK_STOCK_MEDIA_STOP);
	self->slideshow_cancellable = (_tmp0_ = g_cancellable_new (), _g_object_unref0 (self->slideshow_cancellable), _tmp0_);
	image_view_window_slideshow (self, NULL, NULL);
}


void image_view_window_stop_slideshow (ImageViewWindow* self) {
	g_return_if_fail (self != NULL);
	g_cancellable_cancel (self->slideshow_cancellable);
	if (self->slideshow_timeout != 0) {
		g_source_remove (self->slideshow_timeout);
		g_idle_add_full (G_PRIORITY_DEFAULT_IDLE, self->slideshow_continuation, self->slideshow_continuation_target, NULL);
	}
}


void image_view_window_on_image_control_eos (ImageViewWindow* self) {
	g_return_if_fail (self != NULL);
	media_control_set_state ((MediaControl*) self->image_control, GST_STATE_READY);
	gtk_notebook_set_current_page (((MediaWindow*) self)->notebook, (gint) MEDIA_WINDOW_TAB_VIDEO);
	if (self->slideshow_continuation != NULL) {
		self->slideshow_timeout = g_timeout_add_seconds_full (G_PRIORITY_DEFAULT, (guint) 2, self->slideshow_continuation, self->slideshow_continuation_target, NULL);
	}
}


static void image_view_window_slideshow_data_free (gpointer _data) {
	ImageViewWindowSlideshowData* data;
	data = _data;
	g_slice_free (ImageViewWindowSlideshowData, data);
}


void image_view_window_slideshow (ImageViewWindow* self, GAsyncReadyCallback _callback_, gpointer _user_data_) {
	ImageViewWindowSlideshowData* _data_;
	_data_ = g_slice_new0 (ImageViewWindowSlideshowData);
	_data_->_async_result = g_simple_async_result_new (G_OBJECT (self), _callback_, _user_data_, image_view_window_slideshow);
	g_simple_async_result_set_op_res_gpointer (_data_->_async_result, _data_, image_view_window_slideshow_data_free);
	_data_->self = self;
	image_view_window_slideshow_co (_data_);
}


void image_view_window_slideshow_finish (ImageViewWindow* self, GAsyncResult* _res_) {
	ImageViewWindowSlideshowData* _data_;
	_data_ = g_simple_async_result_get_op_res_gpointer (G_SIMPLE_ASYNC_RESULT (_res_));
}


static void image_view_window_slideshow_ready (GObject* source_object, GAsyncResult* _res_, gpointer _user_data_) {
	ImageViewWindowSlideshowData* data;
	data = _user_data_;
	data->_res_ = _res_;
	image_view_window_slideshow_co (data);
}


static gboolean _image_view_window_slideshow_co_gsource_func (gpointer self) {
	return image_view_window_slideshow_co (self);
}


static gboolean image_view_window_slideshow_co (ImageViewWindowSlideshowData* data) {
	switch (data->_state_) {
		default:
		g_assert_not_reached ();
		case 0:
		{
			if (!image_view_window_get_and_select_iter (data->self, &data->iter)) {
				data->_tmp0_ = TRUE;
			} else {
				data->_tmp0_ = g_cancellable_is_cancelled (data->self->slideshow_cancellable);
			}
			if (data->_tmp0_) {
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
			data->self->slideshow_continuation = (data->_tmp1_ = _image_view_window_slideshow_co_gsource_func, ((data->self->slideshow_continuation_target_destroy_notify == NULL) ? NULL : data->self->slideshow_continuation_target_destroy_notify (data->self->slideshow_continuation_target), data->self->slideshow_continuation = NULL, data->self->slideshow_continuation_target = NULL, data->self->slideshow_continuation_target_destroy_notify = NULL), data->self->slideshow_continuation_target = data, data->self->slideshow_continuation_target_destroy_notify = NULL, data->_tmp1_);
			{
				data->_tmp2_ = TRUE;
				while (TRUE) {
					if (!data->_tmp2_) {
						if (gtk_tree_model_iter_next ((GtkTreeModel*) data->self->iconlist_store, &data->iter)) {
							data->_tmp3_ = !g_cancellable_is_cancelled (data->self->slideshow_cancellable);
						} else {
							data->_tmp3_ = FALSE;
						}
						if (!data->_tmp3_) {
							break;
						}
					}
					data->_tmp2_ = FALSE;
					data->path = gtk_tree_model_get_path ((GtkTreeModel*) data->self->iconlist_store, &data->iter);
					gtk_icon_view_select_path (data->self->icon_view, data->path);
					gtk_icon_view_item_activated (data->self->icon_view, data->path);
					data->_state_ = 1;
					return FALSE;
					case 1:
					;
					data->self->slideshow_timeout = (guint) 0;
					_gtk_tree_path_free0 (data->path);
				}
			}
			data->self->slideshow_continuation = (data->_tmp4_ = NULL, ((data->self->slideshow_continuation_target_destroy_notify == NULL) ? NULL : data->self->slideshow_continuation_target_destroy_notify (data->self->slideshow_continuation_target), data->self->slideshow_continuation = NULL, data->self->slideshow_continuation_target = NULL, data->self->slideshow_continuation_target_destroy_notify = NULL), data->self->slideshow_continuation_target = NULL, data->self->slideshow_continuation_target_destroy_notify = NULL, data->_tmp4_);
			data->self->slideshow_cancellable = (data->_tmp5_ = NULL, _g_object_unref0 (data->self->slideshow_cancellable), data->_tmp5_);
			image_view_window_close (data->self);
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


static gpointer _gtk_tree_path_copy0 (gpointer self) {
	return self ? gtk_tree_path_copy (self) : NULL;
}


gboolean image_view_window_get_and_select_iter (ImageViewWindow* self, GtkTreeIter* iter) {
	gboolean result;
	GtkTreePath* path;
	GList* selected;
	g_return_val_if_fail (self != NULL, FALSE);
	path = NULL;
	selected = gtk_icon_view_get_selected_items (self->icon_view);
	if (selected != NULL) {
		GtkTreePath* _tmp0_;
		path = (_tmp0_ = _gtk_tree_path_copy0 ((GtkTreePath*) selected->data), _gtk_tree_path_free0 (path), _tmp0_);
		gtk_tree_model_get_iter ((GtkTreeModel*) self->iconlist_store, iter, path);
		result = TRUE;
		_gtk_tree_path_free0 (path);
		return result;
	} else {
		if (gtk_tree_model_get_iter_first ((GtkTreeModel*) self->iconlist_store, iter)) {
			GtkTreePath* _tmp1_;
			path = (_tmp1_ = gtk_tree_model_get_path ((GtkTreeModel*) self->iconlist_store, iter), _gtk_tree_path_free0 (path), _tmp1_);
			gtk_icon_view_select_path (self->icon_view, path);
			result = TRUE;
			_gtk_tree_path_free0 (path);
			return result;
		}
	}
	result = FALSE;
	_gtk_tree_path_free0 (path);
	return result;
}


void image_view_window_on_chooser_folder_changed (ImageViewWindow* self) {
	char* folder;
	char* _tmp0_;
	g_return_if_fail (self != NULL);
	folder = gtk_file_chooser_get_current_folder ((GtkFileChooser*) self->chooser_button);
	if (_vala_strcmp0 (folder, self->current_folder) == 0) {
		_g_free0 (folder);
		return;
	}
	self->current_folder = (_tmp0_ = g_strdup (folder), _g_free0 (self->current_folder), _tmp0_);
	image_view_window_change_folder (self);
	_g_free0 (folder);
}


static gboolean _image_view_window_retry_change_folder_gsource_func (gpointer self) {
	return image_view_window_retry_change_folder (self);
}


void image_view_window_change_folder (ImageViewWindow* self) {
	g_return_if_fail (self != NULL);
	if (self->fill_icons_cancellable == NULL) {
		GCancellable* _tmp0_;
		g_print ("proceed\n");
		gtk_list_store_clear (self->iconlist_store);
		self->fill_icons_cancellable = (_tmp0_ = g_cancellable_new (), _g_object_unref0 (self->fill_icons_cancellable), _tmp0_);
		icon_list_control_add_folder (self->iconlist_control, self->current_folder, self->fill_icons_cancellable, NULL, NULL);
	} else {
		g_print ("sorry\n");
		g_cancellable_cancel (self->fill_icons_cancellable);
		g_idle_add_full (G_PRIORITY_DEFAULT_IDLE, _image_view_window_retry_change_folder_gsource_func, g_object_ref (self), g_object_unref);
	}
}


gboolean image_view_window_retry_change_folder (ImageViewWindow* self) {
	gboolean result;
	g_return_val_if_fail (self != NULL, FALSE);
	if (self->fill_icons_cancellable == NULL) {
		image_view_window_change_folder (self);
		result = FALSE;
		return result;
	}
	result = TRUE;
	return result;
}


static gboolean _image_view_window_fill_visible_icons_gsource_func (gpointer self) {
	return image_view_window_fill_visible_icons (self);
}


void image_view_window_on_iconlist_files_added (ImageViewWindow* self) {
	g_return_if_fail (self != NULL);
	if (self->fill_icons_cancellable != NULL) {
		g_idle_add_full (G_PRIORITY_DEFAULT_IDLE, _image_view_window_fill_visible_icons_gsource_func, g_object_ref (self), g_object_unref);
	}
}


static gboolean _image_view_window_retry_do_fill_visible_icons_gsource_func (gpointer self) {
	return image_view_window_retry_do_fill_visible_icons (self);
}


void image_view_window_do_fill_visible_icons (ImageViewWindow* self) {
	g_return_if_fail (self != NULL);
	if (self->fill_icons_cancellable == NULL) {
		GCancellable* _tmp0_;
		self->fill_icons_cancellable = (_tmp0_ = g_cancellable_new (), _g_object_unref0 (self->fill_icons_cancellable), _tmp0_);
		image_view_window_fill_visible_icons (self);
	} else {
		if (self->is_filling_icons) {
			g_cancellable_cancel (self->fill_icons_cancellable);
		}
		g_idle_add_full (G_PRIORITY_DEFAULT_IDLE, _image_view_window_retry_do_fill_visible_icons_gsource_func, g_object_ref (self), g_object_unref);
	}
}


gboolean image_view_window_retry_do_fill_visible_icons (ImageViewWindow* self) {
	gboolean result;
	g_return_val_if_fail (self != NULL, FALSE);
	if (self->fill_icons_cancellable == NULL) {
		image_view_window_do_fill_visible_icons (self);
		result = FALSE;
		return result;
	}
	result = TRUE;
	return result;
}


gboolean image_view_window_fill_visible_icons (ImageViewWindow* self) {
	gboolean result;
	GtkTreePath* start;
	GtkTreePath* end;
	GtkTreePath* _tmp5_;
	gboolean _tmp4_;
	GtkTreePath* _tmp3_ = NULL;
	GtkTreePath* _tmp2_;
	gboolean _tmp1_;
	GtkTreePath* _tmp0_ = NULL;
	g_return_val_if_fail (self != NULL, FALSE);
	start = NULL;
	end = NULL;
	_tmp4_ = (_tmp1_ = gtk_icon_view_get_visible_range (self->icon_view, &_tmp0_, &_tmp3_), start = (_tmp2_ = _gtk_tree_path_copy0 (_tmp0_), _gtk_tree_path_free0 (start), _tmp2_), _tmp1_);
	end = (_tmp5_ = _gtk_tree_path_copy0 (_tmp3_), _gtk_tree_path_free0 (end), _tmp5_);
	_tmp4_;
	self->is_filling_icons = TRUE;
	icon_list_control_fill_icons (self->iconlist_control, start, end, self->fill_icons_cancellable, NULL, NULL);
	result = FALSE;
	_gtk_tree_path_free0 (start);
	_gtk_tree_path_free0 (end);
	return result;
}


void image_view_window_on_iconlist_icons_filled (ImageViewWindow* self) {
	GCancellable* _tmp0_;
	g_return_if_fail (self != NULL);
	self->fill_icons_cancellable = (_tmp0_ = NULL, _g_object_unref0 (self->fill_icons_cancellable), _tmp0_);
	self->is_filling_icons = FALSE;
}


static GObject * image_view_window_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GObjectClass * parent_class;
	ImageViewWindow * self;
	parent_class = G_OBJECT_CLASS (image_view_window_parent_class);
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = IMAGE_VIEW_WINDOW (obj);
	{
		image_view_window_setup_model (self);
		image_view_window_setup_widgets (self);
	}
	return obj;
}


static void image_view_window_class_init (ImageViewWindowClass * klass) {
	image_view_window_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->constructor = image_view_window_constructor;
	G_OBJECT_CLASS (klass)->finalize = image_view_window_finalize;
}


static void image_view_window_instance_init (ImageViewWindow * self) {
}


static void image_view_window_finalize (GObject* obj) {
	ImageViewWindow * self;
	self = IMAGE_VIEW_WINDOW (obj);
	{
		if (self->iconlist_control != NULL) {
			guint _tmp0_;
			g_signal_handlers_disconnect_matched (self->iconlist_control, G_SIGNAL_MATCH_ID | G_SIGNAL_MATCH_FUNC | G_SIGNAL_MATCH_DATA, (g_signal_parse_name ("files-added", TYPE_ICON_LIST_CONTROL, &_tmp0_, NULL, FALSE), _tmp0_), 0, NULL, (GCallback) _image_view_window_on_iconlist_files_added_icon_list_control_files_added, self);
		}
	}
	_g_object_unref0 (self->chooser_button);
	_g_object_unref0 (self->icon_view);
	_g_object_unref0 (self->video_area);
	_g_object_unref0 (self->iconlist_store);
	_g_object_unref0 (self->iconlist_control);
	_g_object_unref0 (self->image_control);
	_g_free0 (self->current_folder);
	_g_object_unref0 (self->image_button);
	_g_object_unref0 (self->slideshow_button);
	(self->slideshow_continuation_target_destroy_notify == NULL) ? NULL : self->slideshow_continuation_target_destroy_notify (self->slideshow_continuation_target);
	self->slideshow_continuation = NULL;
	self->slideshow_continuation_target = NULL;
	self->slideshow_continuation_target_destroy_notify = NULL;
	_g_object_unref0 (self->slideshow_cancellable);
	(self->fill_icons_continuation_target_destroy_notify == NULL) ? NULL : self->fill_icons_continuation_target_destroy_notify (self->fill_icons_continuation_target);
	self->fill_icons_continuation = NULL;
	self->fill_icons_continuation_target = NULL;
	self->fill_icons_continuation_target_destroy_notify = NULL;
	_g_object_unref0 (self->fill_icons_cancellable);
	G_OBJECT_CLASS (image_view_window_parent_class)->finalize (obj);
}


GType image_view_window_get_type (void) {
	static GType image_view_window_type_id = 0;
	if (image_view_window_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (ImageViewWindowClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) image_view_window_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (ImageViewWindow), 0, (GInstanceInitFunc) image_view_window_instance_init, NULL };
		image_view_window_type_id = g_type_register_static (TYPE_MEDIA_WINDOW, "ImageViewWindow", &g_define_type_info, 0);
	}
	return image_view_window_type_id;
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




