/* error-dialog.c generated by valac, the Vala compiler
 * generated from error-dialog.gs, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <pango/pango.h>
#include <gdk/gdk.h>


#define TYPE_DEBUG_DIALOG (debug_dialog_get_type ())
#define DEBUG_DIALOG(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_DEBUG_DIALOG, DebugDialog))
#define DEBUG_DIALOG_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_DEBUG_DIALOG, DebugDialogClass))
#define IS_DEBUG_DIALOG(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_DEBUG_DIALOG))
#define IS_DEBUG_DIALOG_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_DEBUG_DIALOG))
#define DEBUG_DIALOG_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_DEBUG_DIALOG, DebugDialogClass))

typedef struct _DebugDialog DebugDialog;
typedef struct _DebugDialogClass DebugDialogClass;
typedef struct _DebugDialogPrivate DebugDialogPrivate;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))

struct _DebugDialog {
	GtkDialog parent_instance;
	DebugDialogPrivate * priv;
	GtkTextBuffer* text_buffer;
	gint errors_n;
};

struct _DebugDialogClass {
	GtkDialogClass parent_class;
};


static gpointer debug_dialog_parent_class = NULL;

GType debug_dialog_get_type (void);
enum  {
	DEBUG_DIALOG_DUMMY_PROPERTY
};
DebugDialog* debug_dialog_new (GtkWindow* parent);
DebugDialog* debug_dialog_construct (GType object_type, GtkWindow* parent);
void debug_dialog_text_insert_new_line (DebugDialog* self, GtkTextIter* iter);
void debug_dialog_add_error_debug (DebugDialog* self, GError* _error_, const char* debug);
GtkBox* debug_dialog_new_error_box (DebugDialog* self);
static void _lambda1_ (DebugDialog* self);
static void __lambda1__gtk_dialog_response (DebugDialog* _sender, gint response_id, gpointer self);
static gboolean _lambda2_ (DebugDialog* self);
static gboolean __lambda2__gtk_widget_delete_event (DebugDialog* _sender, GdkEvent* event, gpointer self);
static GObject * debug_dialog_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static void debug_dialog_finalize (GObject* obj);
static void _lambda3_ (GtkDialog* widget, gint response);
static void __lambda3__gtk_dialog_response (GtkDialog* _sender, gint response_id, gpointer self);
void error_dialog (GError* _error_);



DebugDialog* debug_dialog_construct (GType object_type, GtkWindow* parent) {
	DebugDialog * self;
	gint width = 0;
	gint height = 0;
	g_return_val_if_fail (parent != NULL, NULL);
	self = g_object_newv (object_type, 0, NULL);
	gtk_window_get_size (parent, &width, &height);
	gtk_window_set_default_size ((GtkWindow*) self, (3 * width) / 4, (3 * height) / 4);
	gtk_window_set_transient_for ((GtkWindow*) self, parent);
	return self;
}


DebugDialog* debug_dialog_new (GtkWindow* parent) {
	return debug_dialog_construct (TYPE_DEBUG_DIALOG, parent);
}


void debug_dialog_add_error_debug (DebugDialog* self, GError* _error_, const char* debug) {
	GtkTextIter iter = {0};
	g_return_if_fail (self != NULL);
	g_return_if_fail (debug != NULL);
	self->errors_n++;
	if (self->errors_n > 1) {
		char* _tmp0_;
		gtk_window_set_title ((GtkWindow*) self, _tmp0_ = g_strdup_printf ("%d errors", self->errors_n));
		_g_free0 (_tmp0_);
	}
	gtk_text_buffer_get_end_iter (self->text_buffer, &iter);
	debug_dialog_text_insert_new_line (self, &iter);
	gtk_text_buffer_insert_with_tags_by_name (self->text_buffer, &iter, _error_->message, -1, "bold", NULL, NULL);
	debug_dialog_text_insert_new_line (self, &iter);
	if (debug != NULL) {
		gtk_text_buffer_insert (self->text_buffer, &iter, debug, -1);
		debug_dialog_text_insert_new_line (self, &iter);
	}
}


void debug_dialog_text_insert_new_line (DebugDialog* self, GtkTextIter* iter) {
	g_return_if_fail (self != NULL);
	gtk_text_buffer_insert (self->text_buffer, iter, "\n", -1);
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


GtkBox* debug_dialog_new_error_box (DebugDialog* self) {
	GtkBox* result;
	GtkHBox* box;
	GtkImage* image;
	GtkVSeparator* separator;
	GtkScrolledWindow* scrolled_window;
	GtkTextView* text_view;
	GtkTextBuffer* _tmp0_;
	g_return_val_if_fail (self != NULL, NULL);
	box = g_object_ref_sink ((GtkHBox*) gtk_hbox_new (FALSE, 0));
	image = g_object_ref_sink ((GtkImage*) gtk_image_new_from_stock (GTK_STOCK_DIALOG_ERROR, GTK_ICON_SIZE_DIALOG));
	gtk_box_pack_start ((GtkBox*) box, (GtkWidget*) image, FALSE, FALSE, (guint) 3);
	separator = g_object_ref_sink ((GtkVSeparator*) gtk_vseparator_new ());
	gtk_box_pack_start ((GtkBox*) box, (GtkWidget*) separator, FALSE, FALSE, (guint) 0);
	scrolled_window = g_object_ref_sink ((GtkScrolledWindow*) gtk_scrolled_window_new (NULL, NULL));
	gtk_box_pack_start ((GtkBox*) box, (GtkWidget*) scrolled_window, TRUE, TRUE, (guint) 0);
	gtk_scrolled_window_set_policy (scrolled_window, GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	text_view = g_object_ref_sink ((GtkTextView*) gtk_text_view_new ());
	gtk_container_add ((GtkContainer*) scrolled_window, (GtkWidget*) text_view);
	gtk_text_view_set_editable (text_view, FALSE);
	gtk_text_view_set_cursor_visible (text_view, FALSE);
	gtk_text_view_set_wrap_mode (text_view, GTK_WRAP_WORD);
	self->text_buffer = (_tmp0_ = _g_object_ref0 (gtk_text_view_get_buffer (text_view)), _g_object_unref0 (self->text_buffer), _tmp0_);
	gtk_widget_show_all ((GtkWidget*) box);
	result = (GtkBox*) box;
	_g_object_unref0 (image);
	_g_object_unref0 (separator);
	_g_object_unref0 (scrolled_window);
	_g_object_unref0 (text_view);
	return result;
}


static void _lambda1_ (DebugDialog* self) {
	g_signal_emit_by_name (self, "closed");
	gtk_object_destroy ((GtkObject*) self);
}


static void __lambda1__gtk_dialog_response (DebugDialog* _sender, gint response_id, gpointer self) {
	_lambda1_ (self);
}


static gboolean _lambda2_ (DebugDialog* self) {
	gboolean result;
	g_signal_emit_by_name (self, "closed");
}


static gboolean __lambda2__gtk_widget_delete_event (DebugDialog* _sender, GdkEvent* event, gpointer self) {
	return _lambda2_ (self);
}


static GObject * debug_dialog_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GObjectClass * parent_class;
	DebugDialog * self;
	parent_class = G_OBJECT_CLASS (debug_dialog_parent_class);
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = DEBUG_DIALOG (obj);
	{
		GtkWidget* _tmp0_;
		GtkBox* content_area;
		GtkBox* _tmp1_;
		gtk_window_set_title ((GtkWindow*) self, "Error");
		gtk_dialog_add_button ((GtkDialog*) self, GTK_STOCK_CLOSE, -1);
		gtk_window_set_modal ((GtkWindow*) self, TRUE);
		content_area = _g_object_ref0 ((_tmp0_ = gtk_dialog_get_content_area ((GtkDialog*) self), GTK_IS_BOX (_tmp0_) ? ((GtkBox*) _tmp0_) : NULL));
		gtk_container_add ((GtkContainer*) content_area, (GtkWidget*) (_tmp1_ = debug_dialog_new_error_box (self)));
		_g_object_unref0 (_tmp1_);
		gtk_text_buffer_create_tag (self->text_buffer, "bold", "weight", PANGO_WEIGHT_BOLD, NULL, NULL);
		g_signal_connect_object ((GtkDialog*) self, "response", (GCallback) __lambda1__gtk_dialog_response, self, 0);
		g_signal_connect_object ((GtkWidget*) self, "delete-event", (GCallback) __lambda2__gtk_widget_delete_event, self, 0);
		_g_object_unref0 (content_area);
	}
	return obj;
}


static void debug_dialog_class_init (DebugDialogClass * klass) {
	debug_dialog_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->constructor = debug_dialog_constructor;
	G_OBJECT_CLASS (klass)->finalize = debug_dialog_finalize;
	g_signal_new ("closed", TYPE_DEBUG_DIALOG, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);
}


static void debug_dialog_instance_init (DebugDialog * self) {
}


static void debug_dialog_finalize (GObject* obj) {
	DebugDialog * self;
	self = DEBUG_DIALOG (obj);
	_g_object_unref0 (self->text_buffer);
	G_OBJECT_CLASS (debug_dialog_parent_class)->finalize (obj);
}


GType debug_dialog_get_type (void) {
	static GType debug_dialog_type_id = 0;
	if (debug_dialog_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (DebugDialogClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) debug_dialog_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (DebugDialog), 0, (GInstanceInitFunc) debug_dialog_instance_init, NULL };
		debug_dialog_type_id = g_type_register_static (GTK_TYPE_DIALOG, "DebugDialog", &g_define_type_info, 0);
	}
	return debug_dialog_type_id;
}


static void _lambda3_ (GtkDialog* widget, gint response) {
	g_return_if_fail (widget != NULL);
	if (widget != NULL) {
		gtk_object_destroy ((GtkObject*) widget);
	}
}


static void __lambda3__gtk_dialog_response (GtkDialog* _sender, gint response_id, gpointer self) {
	_lambda3_ (_sender, response_id);
}


void error_dialog (GError* _error_) {
	GtkDialog* dialog;
	dialog = (GtkDialog*) g_object_ref_sink ((GtkMessageDialog*) gtk_message_dialog_new (NULL, 0, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "%s", _error_->message));
	gtk_window_set_title ((GtkWindow*) dialog, "Error");
	g_signal_connect (dialog, "response", (GCallback) __lambda3__gtk_dialog_response, NULL);
	gtk_dialog_run (dialog);
	_g_object_unref0 (dialog);
}




