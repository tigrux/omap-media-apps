/* imageview-window.c generated by valac, the Vala compiler
 * generated from imageview-window.gs, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <gio/gio.h>
#include <stdlib.h>
#include <string.h>
#include <gdk-pixbuf/gdk-pixdata.h>


#define TYPE_IMAGE_LIST_COL (image_list_col_get_type ())

#define TYPE_IMAGE_VIEW_WINDOW (image_view_window_get_type ())
#define IMAGE_VIEW_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_IMAGE_VIEW_WINDOW, ImageViewWindow))
#define IMAGE_VIEW_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_IMAGE_VIEW_WINDOW, ImageViewWindowClass))
#define IS_IMAGE_VIEW_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_IMAGE_VIEW_WINDOW))
#define IS_IMAGE_VIEW_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_IMAGE_VIEW_WINDOW))
#define IMAGE_VIEW_WINDOW_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_IMAGE_VIEW_WINDOW, ImageViewWindowClass))

typedef struct _ImageViewWindow ImageViewWindow;
typedef struct _ImageViewWindowClass ImageViewWindowClass;
typedef struct _ImageViewWindowPrivate ImageViewWindowPrivate;

#define TYPE_ICON_LIST_CONTROL (icon_list_control_get_type ())
#define ICON_LIST_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_ICON_LIST_CONTROL, IconListControl))
#define ICON_LIST_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_ICON_LIST_CONTROL, IconListControlClass))
#define IS_ICON_LIST_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_ICON_LIST_CONTROL))
#define IS_ICON_LIST_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_ICON_LIST_CONTROL))
#define ICON_LIST_CONTROL_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_ICON_LIST_CONTROL, IconListControlClass))

typedef struct _IconListControl IconListControl;
typedef struct _IconListControlClass IconListControlClass;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))

typedef enum  {
	IMAGE_LIST_COL_TEXT,
	IMAGE_LIST_COL_FILE,
	IMAGE_LIST_COL_PIXBUF,
	IMAGE_LIST_COL_VALID
} ImageListCol;

struct _ImageViewWindow {
	GtkWindow parent_instance;
	ImageViewWindowPrivate * priv;
	GtkFileChooserButton* chooser_button;
	GtkIconView* icon_view;
	GtkListStore* iconlist_store;
	IconListControl* iconlist_control;
	GCancellable* cancellable;
};

struct _ImageViewWindowClass {
	GtkWindowClass parent_class;
};


static gpointer image_view_window_parent_class = NULL;

GType image_list_col_get_type (void);
GType image_view_window_get_type (void);
GType icon_list_control_get_type (void);
enum  {
	IMAGE_VIEW_WINDOW_DUMMY_PROPERTY
};
IconListControl* icon_list_control_new (GtkListStore* model, GError** error);
IconListControl* icon_list_control_construct (GType object_type, GtkListStore* model, GError** error);
void image_view_window_on_iconlist_done (ImageViewWindow* self);
static void _image_view_window_on_iconlist_done_icon_list_control_done (IconListControl* _sender, gpointer self);
ImageViewWindow* image_view_window_new (GError** error);
ImageViewWindow* image_view_window_construct (GType object_type, GError** error);
#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 480
static void _gtk_main_quit_gtk_object_destroy (ImageViewWindow* _sender, gpointer self);
void image_view_window_on_chooser_folder_changed (ImageViewWindow* self);
static void _image_view_window_on_chooser_folder_changed_gtk_file_chooser_current_folder_changed (GtkFileChooserButton* _sender, gpointer self);
void image_view_window_setup_widgets (ImageViewWindow* self);
void icon_list_control_add_folder (IconListControl* self, const char* dirname, GCancellable* cancellable, GAsyncReadyCallback _callback_, gpointer _user_data_);
void icon_list_control_add_folder_finish (IconListControl* self, GAsyncResult* _res_);
gboolean image_view_window_retry_chooser_folder_change (ImageViewWindow* self);
static gboolean _image_view_window_retry_chooser_folder_change_gsource_func (gpointer self);
GtkListStore* image_view_window_new_imagelist_store (ImageViewWindow* self);
static GObject * image_view_window_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static void image_view_window_finalize (GObject* obj);




GType image_list_col_get_type (void) {
	static GType image_list_col_type_id = 0;
	if (G_UNLIKELY (image_list_col_type_id == 0)) {
		static const GEnumValue values[] = {{IMAGE_LIST_COL_TEXT, "IMAGE_LIST_COL_TEXT", "text"}, {IMAGE_LIST_COL_FILE, "IMAGE_LIST_COL_FILE", "file"}, {IMAGE_LIST_COL_PIXBUF, "IMAGE_LIST_COL_PIXBUF", "pixbuf"}, {IMAGE_LIST_COL_VALID, "IMAGE_LIST_COL_VALID", "valid"}, {0, NULL, NULL}};
		image_list_col_type_id = g_enum_register_static ("ImageListCol", values);
	}
	return image_list_col_type_id;
}


static void _image_view_window_on_iconlist_done_icon_list_control_done (IconListControl* _sender, gpointer self) {
	image_view_window_on_iconlist_done (self);
}


ImageViewWindow* image_view_window_construct (GType object_type, GError** error) {
	GError * _inner_error_;
	ImageViewWindow * self;
	IconListControl* _tmp0_;
	IconListControl* _tmp1_;
	_inner_error_ = NULL;
	self = g_object_newv (object_type, 0, NULL);
	_tmp0_ = icon_list_control_new (self->iconlist_store, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return NULL;
	}
	self->iconlist_control = (_tmp1_ = _tmp0_, _g_object_unref0 (self->iconlist_control), _tmp1_);
	g_signal_connect_object (self->iconlist_control, "done", (GCallback) _image_view_window_on_iconlist_done_icon_list_control_done, self, 0);
	return self;
}


ImageViewWindow* image_view_window_new (GError** error) {
	return image_view_window_construct (TYPE_IMAGE_VIEW_WINDOW, error);
}


static void _gtk_main_quit_gtk_object_destroy (ImageViewWindow* _sender, gpointer self) {
	gtk_main_quit ();
}


static void _image_view_window_on_chooser_folder_changed_gtk_file_chooser_current_folder_changed (GtkFileChooserButton* _sender, gpointer self) {
	image_view_window_on_chooser_folder_changed (self);
}


void image_view_window_setup_widgets (ImageViewWindow* self) {
	GtkVBox* main_box;
	GtkHBox* buttons_box;
	GtkFileChooserButton* _tmp0_;
	GtkScrolledWindow* scrolled_window;
	GtkIconView* _tmp1_;
	g_return_if_fail (self != NULL);
	gtk_window_set_default_size ((GtkWindow*) self, DEFAULT_WIDTH, DEFAULT_HEIGHT);
	g_signal_connect ((GtkObject*) self, "destroy", (GCallback) _gtk_main_quit_gtk_object_destroy, NULL);
	main_box = g_object_ref_sink ((GtkVBox*) gtk_vbox_new (FALSE, 6));
	gtk_container_add ((GtkContainer*) self, (GtkWidget*) main_box);
	buttons_box = g_object_ref_sink ((GtkHBox*) gtk_hbox_new (FALSE, 6));
	gtk_box_pack_start ((GtkBox*) main_box, (GtkWidget*) buttons_box, FALSE, FALSE, (guint) 0);
	self->chooser_button = (_tmp0_ = g_object_ref_sink ((GtkFileChooserButton*) gtk_file_chooser_button_new ("Select folder", GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER)), _g_object_unref0 (self->chooser_button), _tmp0_);
	gtk_box_pack_start ((GtkBox*) buttons_box, (GtkWidget*) self->chooser_button, TRUE, TRUE, (guint) 0);
	g_signal_connect_object ((GtkFileChooser*) self->chooser_button, "current-folder-changed", (GCallback) _image_view_window_on_chooser_folder_changed_gtk_file_chooser_current_folder_changed, self, 0);
	scrolled_window = g_object_ref_sink ((GtkScrolledWindow*) gtk_scrolled_window_new (NULL, NULL));
	gtk_box_pack_start ((GtkBox*) main_box, (GtkWidget*) scrolled_window, TRUE, TRUE, (guint) 0);
	gtk_scrolled_window_set_policy (scrolled_window, GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	self->icon_view = (_tmp1_ = g_object_ref_sink ((GtkIconView*) gtk_icon_view_new ()), _g_object_unref0 (self->icon_view), _tmp1_);
	gtk_container_add ((GtkContainer*) scrolled_window, (GtkWidget*) self->icon_view);
	gtk_icon_view_set_model (self->icon_view, (GtkTreeModel*) self->iconlist_store);
	gtk_icon_view_set_text_column (self->icon_view, (gint) IMAGE_LIST_COL_TEXT);
	gtk_icon_view_set_pixbuf_column (self->icon_view, (gint) IMAGE_LIST_COL_PIXBUF);
	gtk_icon_view_set_row_spacing (self->icon_view, 0);
	gtk_icon_view_set_column_spacing (self->icon_view, 0);
	gtk_icon_view_set_spacing (self->icon_view, 0);
	gtk_icon_view_set_margin (self->icon_view, 0);
	gtk_icon_view_set_item_padding (self->icon_view, 0);
	gtk_widget_show_all ((GtkWidget*) main_box);
	_g_object_unref0 (main_box);
	_g_object_unref0 (buttons_box);
	_g_object_unref0 (scrolled_window);
}


static gboolean _image_view_window_retry_chooser_folder_change_gsource_func (gpointer self) {
	return image_view_window_retry_chooser_folder_change (self);
}


void image_view_window_on_chooser_folder_changed (ImageViewWindow* self) {
	g_return_if_fail (self != NULL);
	if (self->cancellable == NULL) {
		char* folder;
		GCancellable* _tmp0_;
		folder = gtk_file_chooser_get_filename ((GtkFileChooser*) self->chooser_button);
		gtk_list_store_clear (self->iconlist_store);
		self->cancellable = (_tmp0_ = g_cancellable_new (), _g_object_unref0 (self->cancellable), _tmp0_);
		icon_list_control_add_folder (self->iconlist_control, folder, self->cancellable, NULL, NULL);
		_g_free0 (folder);
	} else {
		g_cancellable_cancel (self->cancellable);
		g_idle_add_full (G_PRIORITY_DEFAULT_IDLE, _image_view_window_retry_chooser_folder_change_gsource_func, g_object_ref (self), g_object_unref);
	}
}


gboolean image_view_window_retry_chooser_folder_change (ImageViewWindow* self) {
	gboolean result;
	g_return_val_if_fail (self != NULL, FALSE);
	if (self->cancellable == NULL) {
		image_view_window_on_chooser_folder_changed (self);
	} else {
		g_idle_add_full (G_PRIORITY_DEFAULT_IDLE, _image_view_window_retry_chooser_folder_change_gsource_func, g_object_ref (self), g_object_unref);
	}
	result = FALSE;
	return result;
}


void image_view_window_on_iconlist_done (ImageViewWindow* self) {
	GCancellable* _tmp0_;
	g_return_if_fail (self != NULL);
	g_print ("Work done\n");
	self->cancellable = (_tmp0_ = NULL, _g_object_unref0 (self->cancellable), _tmp0_);
}


GtkListStore* image_view_window_new_imagelist_store (ImageViewWindow* self) {
	GtkListStore* result;
	GType s;
	GType p;
	GType b;
	GtkListStore* model;
	g_return_val_if_fail (self != NULL, NULL);
	s = G_TYPE_STRING;
	p = GDK_TYPE_PIXBUF;
	b = G_TYPE_BOOLEAN;
	model = gtk_list_store_new (4, s, s, p, b, NULL);
	result = model;
	return result;
}


static GObject * image_view_window_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GObjectClass * parent_class;
	ImageViewWindow * self;
	parent_class = G_OBJECT_CLASS (image_view_window_parent_class);
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = IMAGE_VIEW_WINDOW (obj);
	{
		GtkListStore* _tmp0_;
		self->iconlist_store = (_tmp0_ = image_view_window_new_imagelist_store (self), _g_object_unref0 (self->iconlist_store), _tmp0_);
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
	_g_object_unref0 (self->chooser_button);
	_g_object_unref0 (self->icon_view);
	_g_object_unref0 (self->iconlist_store);
	_g_object_unref0 (self->iconlist_control);
	_g_object_unref0 (self->cancellable);
	G_OBJECT_CLASS (image_view_window_parent_class)->finalize (obj);
}


GType image_view_window_get_type (void) {
	static GType image_view_window_type_id = 0;
	if (image_view_window_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (ImageViewWindowClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) image_view_window_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (ImageViewWindow), 0, (GInstanceInitFunc) image_view_window_instance_init, NULL };
		image_view_window_type_id = g_type_register_static (GTK_TYPE_WINDOW, "ImageViewWindow", &g_define_type_info, 0);
	}
	return image_view_window_type_id;
}




