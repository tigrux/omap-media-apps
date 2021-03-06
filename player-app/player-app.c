/* player-app.c generated by valac 0.10.0, the Vala compiler
 * generated from player-app.gs, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <gst/gst.h>
#include <gtk/gtk.h>
#include <common.h>


#define OMAP_TYPE_PLAYER_WINDOW (omap_player_window_get_type ())
#define OMAP_PLAYER_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), OMAP_TYPE_PLAYER_WINDOW, OmapPlayerWindow))
#define OMAP_PLAYER_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), OMAP_TYPE_PLAYER_WINDOW, OmapPlayerWindowClass))
#define OMAP_IS_PLAYER_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), OMAP_TYPE_PLAYER_WINDOW))
#define OMAP_IS_PLAYER_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), OMAP_TYPE_PLAYER_WINDOW))
#define OMAP_PLAYER_WINDOW_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), OMAP_TYPE_PLAYER_WINDOW, OmapPlayerWindowClass))

typedef struct _OmapPlayerWindow OmapPlayerWindow;
typedef struct _OmapPlayerWindowClass OmapPlayerWindowClass;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))



void _vala_main (char** args, int args_length1);
OmapPlayerWindow* omap_player_window_new (void);
OmapPlayerWindow* omap_player_window_construct (GType object_type);
GType omap_player_window_get_type (void) G_GNUC_CONST;



void _vala_main (char** args, int args_length1) {
	OmapPlayerWindow* window;
	gst_init (&args_length1, &args);
	gtk_init (&args_length1, &args);
	window = g_object_ref_sink (omap_player_window_new ());
	gtk_widget_show ((GtkWidget*) window);
	gtk_main ();
	_g_object_unref0 (window);
}


int main (int argc, char ** argv) {
	g_type_init ();
	_vala_main (argv, argc);
	return 0;
}




