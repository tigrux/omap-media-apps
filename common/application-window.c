/* application-window.c generated by valac, the Vala compiler
 * generated from application-window.gs, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>


#define TYPE_APPLICATION_TAB (application_tab_get_type ())

#define TYPE_APPLICATION_WINDOW (application_window_get_type ())
#define APPLICATION_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_APPLICATION_WINDOW, ApplicationWindow))
#define APPLICATION_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_APPLICATION_WINDOW, ApplicationWindowClass))
#define IS_APPLICATION_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_APPLICATION_WINDOW))
#define IS_APPLICATION_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_APPLICATION_WINDOW))
#define APPLICATION_WINDOW_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_APPLICATION_WINDOW, ApplicationWindowClass))

typedef struct _ApplicationWindow ApplicationWindow;
typedef struct _ApplicationWindowClass ApplicationWindowClass;
typedef struct _ApplicationWindowPrivate ApplicationWindowPrivate;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))

typedef enum  {
	APPLICATION_TAB_LIST,
	APPLICATION_TAB_VIDEO
} ApplicationTab;

struct _ApplicationWindow {
	GtkWindow parent_instance;
	ApplicationWindowPrivate * priv;
	GtkNotebook* notebook;
	GtkToolbar* toolbar;
	GtkVBox* main_box;
};

struct _ApplicationWindowClass {
	GtkWindowClass parent_class;
};


extern gboolean application_window_rc_parsed;
gboolean application_window_rc_parsed = FALSE;
static gpointer application_window_parent_class = NULL;

GType application_tab_get_type (void);
GType application_window_get_type (void);
enum  {
	APPLICATION_WINDOW_DUMMY_PROPERTY
};
gboolean application_window_rc_parse (void);
#define DEFAULT_STYLE "\nstyle \"custom\"\n{\n    GtkRange::slider-width = 24\n    GtkComboBox::arrow-size = 18\n    GtkComboBox::appears-as-list = 1\n    font_name = \"Sans 12\"\n}\n\nwidget_class \"*\" style \"custom\"\n"
void application_window_toolbar_add_expander (ApplicationWindow* self);
void application_window_on_quit (ApplicationWindow* self);
static void _application_window_on_quit_gtk_tool_button_clicked (GtkToolButton* _sender, gpointer self);
void application_window_toolbar_add_quit_button (ApplicationWindow* self);
gboolean application_window_quit (ApplicationWindow* self);
static gboolean _application_window_quit_gsource_func (gpointer self);
ApplicationWindow* application_window_new (void);
ApplicationWindow* application_window_construct (GType object_type);
#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 480
static void _application_window_on_quit_gtk_object_destroy (ApplicationWindow* _sender, gpointer self);
#define ICON_SIZE GTK_ICON_SIZE_DND
static GObject * application_window_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static void application_window_finalize (GObject* obj);




GType application_tab_get_type (void) {
	static GType application_tab_type_id = 0;
	if (G_UNLIKELY (application_tab_type_id == 0)) {
		static const GEnumValue values[] = {{APPLICATION_TAB_LIST, "APPLICATION_TAB_LIST", "list"}, {APPLICATION_TAB_VIDEO, "APPLICATION_TAB_VIDEO", "video"}, {0, NULL, NULL}};
		application_tab_type_id = g_enum_register_static ("ApplicationTab", values);
	}
	return application_tab_type_id;
}


gboolean application_window_rc_parse (void) {
	gboolean result;
	gtk_rc_parse_string (DEFAULT_STYLE);
	result = TRUE;
	return result;
}


static void _application_window_on_quit_gtk_tool_button_clicked (GtkToolButton* _sender, gpointer self) {
	application_window_on_quit (self);
}


void application_window_toolbar_add_quit_button (ApplicationWindow* self) {
	GtkToolButton* quit_button;
	g_return_if_fail (self != NULL);
	application_window_toolbar_add_expander (self);
	quit_button = g_object_ref_sink ((GtkToolButton*) gtk_tool_button_new_from_stock (GTK_STOCK_QUIT));
	gtk_container_add ((GtkContainer*) self->toolbar, (GtkWidget*) quit_button);
	g_signal_connect_object (quit_button, "clicked", (GCallback) _application_window_on_quit_gtk_tool_button_clicked, self, 0);
	_g_object_unref0 (quit_button);
}


void application_window_toolbar_add_expander (ApplicationWindow* self) {
	GtkSeparatorToolItem* expander_item;
	g_return_if_fail (self != NULL);
	expander_item = g_object_ref_sink ((GtkSeparatorToolItem*) gtk_separator_tool_item_new ());
	gtk_tool_item_set_expand ((GtkToolItem*) expander_item, TRUE);
	gtk_separator_tool_item_set_draw (expander_item, FALSE);
	gtk_container_add ((GtkContainer*) self->toolbar, (GtkWidget*) expander_item);
	_g_object_unref0 (expander_item);
}


static gboolean _application_window_quit_gsource_func (gpointer self) {
	return application_window_quit (self);
}


void application_window_on_quit (ApplicationWindow* self) {
	g_return_if_fail (self != NULL);
	g_idle_add_full (G_PRIORITY_DEFAULT_IDLE, _application_window_quit_gsource_func, g_object_ref (self), g_object_unref);
}


gboolean application_window_quit (ApplicationWindow* self) {
	gboolean result;
	g_return_val_if_fail (self != NULL, FALSE);
	gtk_main_quit ();
	result = FALSE;
	return result;
}


ApplicationWindow* application_window_construct (GType object_type) {
	ApplicationWindow * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


ApplicationWindow* application_window_new (void) {
	return application_window_construct (TYPE_APPLICATION_WINDOW);
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


static void _application_window_on_quit_gtk_object_destroy (ApplicationWindow* _sender, gpointer self) {
	application_window_on_quit (self);
}


static GObject * application_window_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GObjectClass * parent_class;
	ApplicationWindow * self;
	parent_class = G_OBJECT_CLASS (application_window_parent_class);
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = APPLICATION_WINDOW (obj);
	{
		GtkSettings* settings;
		GtkVBox* _tmp0_;
		GtkToolbar* _tmp1_;
		GtkNotebook* _tmp2_;
		settings = _g_object_ref0 (gtk_widget_get_settings ((GtkWidget*) self));
		g_object_set ((GObject*) settings, "gtk-touchscreen-mode", TRUE, NULL);
		gtk_window_set_default_size ((GtkWindow*) self, DEFAULT_WIDTH, DEFAULT_HEIGHT);
		g_signal_connect_object ((GtkObject*) self, "destroy", (GCallback) _application_window_on_quit_gtk_object_destroy, self, 0);
		self->main_box = (_tmp0_ = g_object_ref_sink ((GtkVBox*) gtk_vbox_new (FALSE, 0)), _g_object_unref0 (self->main_box), _tmp0_);
		gtk_container_add ((GtkContainer*) self, (GtkWidget*) self->main_box);
		self->toolbar = (_tmp1_ = g_object_ref_sink ((GtkToolbar*) gtk_toolbar_new ()), _g_object_unref0 (self->toolbar), _tmp1_);
		gtk_toolbar_set_icon_size (self->toolbar, ICON_SIZE);
		gtk_box_pack_start ((GtkBox*) self->main_box, (GtkWidget*) self->toolbar, FALSE, FALSE, (guint) 0);
		self->notebook = (_tmp2_ = g_object_ref_sink ((GtkNotebook*) gtk_notebook_new ()), _g_object_unref0 (self->notebook), _tmp2_);
		gtk_notebook_set_show_tabs (self->notebook, FALSE);
		gtk_box_pack_start ((GtkBox*) self->main_box, (GtkWidget*) self->notebook, TRUE, TRUE, (guint) 0);
		gtk_widget_show_all ((GtkWidget*) self->main_box);
		_g_object_unref0 (settings);
	}
	return obj;
}


static void application_window_class_init (ApplicationWindowClass * klass) {
	application_window_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->constructor = application_window_constructor;
	G_OBJECT_CLASS (klass)->finalize = application_window_finalize;
	application_window_rc_parsed = application_window_rc_parse ();
}


static void application_window_instance_init (ApplicationWindow * self) {
}


static void application_window_finalize (GObject* obj) {
	ApplicationWindow * self;
	self = APPLICATION_WINDOW (obj);
	_g_object_unref0 (self->notebook);
	_g_object_unref0 (self->toolbar);
	_g_object_unref0 (self->main_box);
	G_OBJECT_CLASS (application_window_parent_class)->finalize (obj);
}


GType application_window_get_type (void) {
	static GType application_window_type_id = 0;
	if (application_window_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (ApplicationWindowClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) application_window_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (ApplicationWindow), 0, (GInstanceInitFunc) application_window_instance_init, NULL };
		application_window_type_id = g_type_register_static (GTK_TYPE_WINDOW, "ApplicationWindow", &g_define_type_info, 0);
	}
	return application_window_type_id;
}




