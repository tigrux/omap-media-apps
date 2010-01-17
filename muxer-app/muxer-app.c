/* muxer-app.c generated by valac, the Vala compiler
 * generated from muxer-app.gs, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <gst/gst.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>


#define TYPE_APPLICATION_WINDOW (application_window_get_type ())
#define APPLICATION_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_APPLICATION_WINDOW, ApplicationWindow))
#define APPLICATION_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_APPLICATION_WINDOW, ApplicationWindowClass))
#define IS_APPLICATION_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_APPLICATION_WINDOW))
#define IS_APPLICATION_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_APPLICATION_WINDOW))
#define APPLICATION_WINDOW_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_APPLICATION_WINDOW, ApplicationWindowClass))

typedef struct _ApplicationWindow ApplicationWindow;
typedef struct _ApplicationWindowClass ApplicationWindowClass;

#define TYPE_MUXER_WINDOW (muxer_window_get_type ())
#define MUXER_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_MUXER_WINDOW, MuxerWindow))
#define MUXER_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_MUXER_WINDOW, MuxerWindowClass))
#define IS_MUXER_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_MUXER_WINDOW))
#define IS_MUXER_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_MUXER_WINDOW))
#define MUXER_WINDOW_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_MUXER_WINDOW, MuxerWindowClass))

typedef struct _MuxerWindow MuxerWindow;
typedef struct _MuxerWindowClass MuxerWindowClass;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))



#define DEFAULT_STYLE "\nstyle \"custom\"\n{\n    GtkRange::slider-width = 24\n    GtkComboBox::arrow-size = 18\n    GtkComboBox::appears-as-list = 1\n    font_name = \"Sans 12\"\n}\n\nwidget_class \"*\" style \"custom\"\n"
MuxerWindow* muxer_window_new (void);
MuxerWindow* muxer_window_construct (GType object_type);
GType application_window_get_type (void);
GType muxer_window_get_type (void);
void _main (char** args, int args_length1);



void _main (char** args, int args_length1) {
	MuxerWindow* window;
	gst_init (&args_length1, &args);
	gtk_init (&args_length1, &args);
	gtk_rc_parse_string (DEFAULT_STYLE);
	window = g_object_ref_sink (muxer_window_new ());
	gtk_widget_show ((GtkWidget*) window);
	gtk_main ();
	_g_object_unref0 (window);
}


int main (int argc, char ** argv) {
	g_type_init ();
	_main (argv, argc);
	return 0;
}




