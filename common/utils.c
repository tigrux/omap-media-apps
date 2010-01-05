/* utils.c generated by valac, the Vala compiler
 * generated from utils.gs, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

#define _g_list_free0(var) ((var == NULL) ? NULL : (var = (g_list_free (var), NULL)))
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))



#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 480
#define ICON_SIZE GTK_ICON_SIZE_DND
GtkWidget* child_widget_at_path (GtkWidget* widget, gint* indices, int indices_length1);
GtkButton* new_button_with_stock_image (const char* stock_id);



static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


GtkWidget* child_widget_at_path (GtkWidget* widget, gint* indices, int indices_length1) {
	GtkWidget* result;
	g_return_val_if_fail (widget != NULL, NULL);
	{
		gint* index_collection;
		int index_collection_length1;
		int index_it;
		index_collection = indices;
		index_collection_length1 = indices_length1;
		for (index_it = 0; index_it < indices_length1; index_it = index_it + 1) {
			gint index;
			index = index_collection[index_it];
			{
				GtkWidget* _tmp0_;
				GtkContainer* container;
				GList* _tmp1_;
				GtkWidget* _tmp2_;
				container = _g_object_ref0 ((_tmp0_ = widget, GTK_IS_CONTAINER (_tmp0_) ? ((GtkContainer*) _tmp0_) : NULL));
				widget = (_tmp2_ = (GtkWidget*) g_list_nth_data (_tmp1_ = gtk_container_get_children (container), (guint) index), GTK_IS_WIDGET (_tmp2_) ? ((GtkWidget*) _tmp2_) : NULL);
				_g_list_free0 (_tmp1_);
				_g_object_unref0 (container);
			}
		}
	}
	result = _g_object_ref0 (widget);
	return result;
}


GtkButton* new_button_with_stock_image (const char* stock_id) {
	GtkButton* result;
	GtkButton* button;
	GtkImage* image;
	g_return_val_if_fail (stock_id != NULL, NULL);
	button = g_object_ref_sink ((GtkButton*) gtk_button_new ());
	gtk_button_set_relief (button, GTK_RELIEF_NONE);
	image = g_object_ref_sink ((GtkImage*) gtk_image_new_from_stock (stock_id, ICON_SIZE));
	gtk_container_add ((GtkContainer*) button, (GtkWidget*) image);
	result = button;
	_g_object_unref0 (image);
	return result;
}




