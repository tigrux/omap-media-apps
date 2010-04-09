/* media-window.c generated by valac, the Vala compiler
 * generated from media-window.gs, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <glib/gstdio.h>


#define OMAP_TYPE_MEDIA_WINDOW (omap_media_window_get_type ())
#define OMAP_MEDIA_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), OMAP_TYPE_MEDIA_WINDOW, OmapMediaWindow))
#define OMAP_MEDIA_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), OMAP_TYPE_MEDIA_WINDOW, OmapMediaWindowClass))
#define OMAP_IS_MEDIA_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), OMAP_TYPE_MEDIA_WINDOW))
#define OMAP_IS_MEDIA_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), OMAP_TYPE_MEDIA_WINDOW))
#define OMAP_MEDIA_WINDOW_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), OMAP_TYPE_MEDIA_WINDOW, OmapMediaWindowClass))

typedef struct _OmapMediaWindow OmapMediaWindow;
typedef struct _OmapMediaWindowClass OmapMediaWindowClass;
typedef struct _OmapMediaWindowPrivate OmapMediaWindowPrivate;

#define OMAP_MEDIA_WINDOW_TYPE_TAB (omap_media_window_tab_get_type ())
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))
#define _gtk_icon_info_free0(var) ((var == NULL) ? NULL : (var = (gtk_icon_info_free (var), NULL)))
#define _g_list_free0(var) ((var == NULL) ? NULL : (var = (g_list_free (var), NULL)))

struct _OmapMediaWindow {
	GtkWindow parent_instance;
	OmapMediaWindowPrivate * priv;
	GtkNotebook* notebook;
	GtkToolbar* toolbar;
	GtkVBox* main_box;
	gboolean is_fullscreen;
};

struct _OmapMediaWindowClass {
	GtkWindowClass parent_class;
};

typedef enum  {
	OMAP_MEDIA_WINDOW_TAB_LIST,
	OMAP_MEDIA_WINDOW_TAB_VIDEO
} OmapMediaWindowTab;


extern gboolean omap_media_window_style_applied;
gboolean omap_media_window_style_applied = FALSE;
static gpointer omap_media_window_parent_class = NULL;

GType omap_media_window_get_type (void);
enum  {
	OMAP_MEDIA_WINDOW_DUMMY_PROPERTY,
	OMAP_MEDIA_WINDOW_FULLSCREEN
};
GType omap_media_window_tab_get_type (void);
gboolean omap_media_window_apply_style (void);
void omap_media_window_lookup_and_set_icon_name (OmapMediaWindow* self, const char* name);
void omap_media_window_toolbar_add_expander (OmapMediaWindow* self);
void omap_media_window_on_quit (OmapMediaWindow* self);
static void _omap_media_window_on_quit_gtk_tool_button_clicked (GtkToolButton* _sender, gpointer self);
void omap_media_window_toolbar_add_quit_button (OmapMediaWindow* self);
gboolean omap_media_window_get_fullscreen (OmapMediaWindow* self);
void omap_media_window_set_fullscreen (OmapMediaWindow* self, gboolean value);
void omap_media_window_toggle_fullscreen (OmapMediaWindow* self);
gboolean omap_media_window_quit (OmapMediaWindow* self);
static gboolean _omap_media_window_quit_gsource_func (gpointer self);
OmapMediaWindow* omap_media_window_new (void);
OmapMediaWindow* omap_media_window_construct (GType object_type);
static void _omap_media_window_on_quit_gtk_object_destroy (OmapMediaWindow* _sender, gpointer self);
static GObject * omap_media_window_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static void omap_media_window_finalize (GObject* obj);
static void omap_media_window_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void omap_media_window_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);
static gint _vala_array_length (gpointer array);



GType omap_media_window_tab_get_type (void) {
	static volatile gsize omap_media_window_tab_type_id__volatile = 0;
	if (g_once_init_enter (&omap_media_window_tab_type_id__volatile)) {
		static const GEnumValue values[] = {{OMAP_MEDIA_WINDOW_TAB_LIST, "OMAP_MEDIA_WINDOW_TAB_LIST", "list"}, {OMAP_MEDIA_WINDOW_TAB_VIDEO, "OMAP_MEDIA_WINDOW_TAB_VIDEO", "video"}, {0, NULL, NULL}};
		GType omap_media_window_tab_type_id;
		omap_media_window_tab_type_id = g_enum_register_static ("OmapMediaWindowTab", values);
		g_once_init_leave (&omap_media_window_tab_type_id__volatile, omap_media_window_tab_type_id);
	}
	return omap_media_window_tab_type_id__volatile;
}


gboolean omap_media_window_apply_style (void) {
	gboolean result = FALSE;
	{
		char** _tmp0_;
		char** dir_collection;
		int dir_collection_length1;
		int dir_it;
		dir_collection = _tmp0_ = g_get_system_data_dirs ();
		dir_collection_length1 = _vala_array_length (_tmp0_);
		for (dir_it = 0; dir_it < _vala_array_length (_tmp0_); dir_it = dir_it + 1) {
			char* dir;
			dir = g_strdup (dir_collection[dir_it]);
			{
				char* rc_file;
				rc_file = g_build_filename (dir, "omap4-apps", "style.rc", NULL);
				if (g_file_test (rc_file, G_FILE_TEST_IS_REGULAR)) {
					gtk_rc_parse (rc_file);
					{
						result = TRUE;
						_g_free0 (dir);
						_g_free0 (rc_file);
						return result;
					}
				}
				_g_free0 (dir);
				_g_free0 (rc_file);
			}
		}
	}
	result = FALSE;
	return result;
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


void omap_media_window_lookup_and_set_icon_name (OmapMediaWindow* self, const char* name) {
	GError * _inner_error_;
	GtkIconTheme* theme;
	GtkIconInfo* icon_info;
	g_return_if_fail (self != NULL);
	g_return_if_fail (name != NULL);
	_inner_error_ = NULL;
	theme = _g_object_ref0 (gtk_icon_theme_get_default ());
	icon_info = gtk_icon_theme_lookup_icon (theme, name, 48, 0);
	if (icon_info != NULL) {
		{
			gtk_window_set_icon_from_file ((GtkWindow*) self, gtk_icon_info_get_filename (icon_info), &_inner_error_);
			if (_inner_error_ != NULL) {
				goto __catch0_g_error;
			}
		}
		goto __finally0;
		__catch0_g_error:
		{
			g_clear_error (&_inner_error_);
			_inner_error_ = NULL;
			{
				;
			}
		}
		__finally0:
		if (_inner_error_ != NULL) {
			_g_object_unref0 (theme);
			_gtk_icon_info_free0 (icon_info);
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
	}
	_g_object_unref0 (theme);
	_gtk_icon_info_free0 (icon_info);
}


static void _omap_media_window_on_quit_gtk_tool_button_clicked (GtkToolButton* _sender, gpointer self) {
	omap_media_window_on_quit (self);
}


void omap_media_window_toolbar_add_quit_button (OmapMediaWindow* self) {
	GtkToolButton* quit_button;
	g_return_if_fail (self != NULL);
	omap_media_window_toolbar_add_expander (self);
	quit_button = g_object_ref_sink ((GtkToolButton*) gtk_tool_button_new_from_stock (GTK_STOCK_QUIT));
	gtk_container_add ((GtkContainer*) self->toolbar, (GtkWidget*) quit_button);
	g_signal_connect_object (quit_button, "clicked", (GCallback) _omap_media_window_on_quit_gtk_tool_button_clicked, self, 0);
	_g_object_unref0 (quit_button);
}


void omap_media_window_toolbar_add_expander (OmapMediaWindow* self) {
	GtkSeparatorToolItem* expander_item;
	g_return_if_fail (self != NULL);
	expander_item = g_object_ref_sink ((GtkSeparatorToolItem*) gtk_separator_tool_item_new ());
	gtk_tool_item_set_expand ((GtkToolItem*) expander_item, TRUE);
	gtk_separator_tool_item_set_draw (expander_item, FALSE);
	gtk_container_add ((GtkContainer*) self->toolbar, (GtkWidget*) expander_item);
	_g_object_unref0 (expander_item);
}


void omap_media_window_toggle_fullscreen (OmapMediaWindow* self) {
	g_return_if_fail (self != NULL);
	omap_media_window_set_fullscreen (self, !omap_media_window_get_fullscreen (self));
}


static gboolean _omap_media_window_quit_gsource_func (gpointer self) {
	return omap_media_window_quit (self);
}


void omap_media_window_on_quit (OmapMediaWindow* self) {
	g_return_if_fail (self != NULL);
	g_idle_add_full (G_PRIORITY_DEFAULT_IDLE, _omap_media_window_quit_gsource_func, g_object_ref (self), g_object_unref);
}


gboolean omap_media_window_quit (OmapMediaWindow* self) {
	gboolean result = FALSE;
	g_return_val_if_fail (self != NULL, FALSE);
	gtk_main_quit ();
	result = FALSE;
	return result;
}


OmapMediaWindow* omap_media_window_construct (GType object_type) {
	OmapMediaWindow * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


OmapMediaWindow* omap_media_window_new (void) {
	return omap_media_window_construct (OMAP_TYPE_MEDIA_WINDOW);
}


gboolean omap_media_window_get_fullscreen (OmapMediaWindow* self) {
	gboolean result;
	g_return_val_if_fail (self != NULL, FALSE);
	result = self->is_fullscreen;
	return result;
}


void omap_media_window_set_fullscreen (OmapMediaWindow* self, gboolean value) {
	g_return_if_fail (self != NULL);
	self->is_fullscreen = value;
	{
		GList* child_collection;
		GList* child_it;
		child_collection = gtk_container_get_children ((GtkContainer*) self->main_box);
		for (child_it = child_collection; child_it != NULL; child_it = child_it->next) {
			GtkWidget* child;
			child = (GtkWidget*) child_it->data;
			{
				if (child != GTK_WIDGET (self->notebook)) {
					if (value) {
						gtk_widget_hide (child);
					} else {
						gtk_widget_show (child);
					}
				}
			}
		}
		_g_list_free0 (child_collection);
	}
	if (value) {
		gtk_window_fullscreen (GTK_WINDOW (self));
	} else {
		gtk_window_unfullscreen (GTK_WINDOW (self));
	}
	g_object_notify ((GObject *) self, "fullscreen");
}


static void _omap_media_window_on_quit_gtk_object_destroy (OmapMediaWindow* _sender, gpointer self) {
	omap_media_window_on_quit (self);
}


static GObject * omap_media_window_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GObjectClass * parent_class;
	OmapMediaWindow * self;
	parent_class = G_OBJECT_CLASS (omap_media_window_parent_class);
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = OMAP_MEDIA_WINDOW (obj);
	{
		GtkSettings* settings;
		GtkVBox* _tmp0_;
		GtkToolbar* _tmp1_;
		GtkNotebook* _tmp2_;
		omap_media_window_lookup_and_set_icon_name (self, g_get_prgname ());
		settings = _g_object_ref0 (gtk_widget_get_settings ((GtkWidget*) self));
		g_object_set (settings, "gtk-touchscreen-mode", TRUE, NULL);
		gtk_window_set_default_size ((GtkWindow*) self, 800, 480);
		g_signal_connect_object ((GtkObject*) self, "destroy", (GCallback) _omap_media_window_on_quit_gtk_object_destroy, self, 0);
		self->main_box = (_tmp0_ = g_object_ref_sink ((GtkVBox*) gtk_vbox_new (FALSE, 0)), _g_object_unref0 (self->main_box), _tmp0_);
		gtk_container_add ((GtkContainer*) self, (GtkWidget*) self->main_box);
		self->toolbar = (_tmp1_ = g_object_ref_sink ((GtkToolbar*) gtk_toolbar_new ()), _g_object_unref0 (self->toolbar), _tmp1_);
		gtk_toolbar_set_icon_size (self->toolbar, (gint) GTK_ICON_SIZE_DND);
		gtk_box_pack_start ((GtkBox*) self->main_box, (GtkWidget*) self->toolbar, FALSE, FALSE, (guint) 0);
		self->notebook = (_tmp2_ = g_object_ref_sink ((GtkNotebook*) gtk_notebook_new ()), _g_object_unref0 (self->notebook), _tmp2_);
		gtk_notebook_set_show_tabs (self->notebook, FALSE);
		gtk_box_pack_start ((GtkBox*) self->main_box, (GtkWidget*) self->notebook, TRUE, TRUE, (guint) 0);
		gtk_widget_show_all ((GtkWidget*) self->main_box);
		_g_object_unref0 (settings);
	}
	return obj;
}


static void omap_media_window_class_init (OmapMediaWindowClass * klass) {
	omap_media_window_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->get_property = omap_media_window_get_property;
	G_OBJECT_CLASS (klass)->set_property = omap_media_window_set_property;
	G_OBJECT_CLASS (klass)->constructor = omap_media_window_constructor;
	G_OBJECT_CLASS (klass)->finalize = omap_media_window_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), OMAP_MEDIA_WINDOW_FULLSCREEN, g_param_spec_boolean ("fullscreen", "fullscreen", "fullscreen", FALSE, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	omap_media_window_style_applied = omap_media_window_apply_style ();
}


static void omap_media_window_instance_init (OmapMediaWindow * self) {
}


static void omap_media_window_finalize (GObject* obj) {
	OmapMediaWindow * self;
	self = OMAP_MEDIA_WINDOW (obj);
	_g_object_unref0 (self->notebook);
	_g_object_unref0 (self->toolbar);
	_g_object_unref0 (self->main_box);
	G_OBJECT_CLASS (omap_media_window_parent_class)->finalize (obj);
}


GType omap_media_window_get_type (void) {
	static volatile gsize omap_media_window_type_id__volatile = 0;
	if (g_once_init_enter (&omap_media_window_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (OmapMediaWindowClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) omap_media_window_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (OmapMediaWindow), 0, (GInstanceInitFunc) omap_media_window_instance_init, NULL };
		GType omap_media_window_type_id;
		omap_media_window_type_id = g_type_register_static (GTK_TYPE_WINDOW, "OmapMediaWindow", &g_define_type_info, 0);
		g_once_init_leave (&omap_media_window_type_id__volatile, omap_media_window_type_id);
	}
	return omap_media_window_type_id__volatile;
}


static void omap_media_window_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	OmapMediaWindow * self;
	self = OMAP_MEDIA_WINDOW (object);
	switch (property_id) {
		case OMAP_MEDIA_WINDOW_FULLSCREEN:
		g_value_set_boolean (value, omap_media_window_get_fullscreen (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void omap_media_window_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	OmapMediaWindow * self;
	self = OMAP_MEDIA_WINDOW (object);
	switch (property_id) {
		case OMAP_MEDIA_WINDOW_FULLSCREEN:
		omap_media_window_set_fullscreen (self, g_value_get_boolean (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static gint _vala_array_length (gpointer array) {
	int length;
	length = 0;
	if (array) {
		while (((gpointer*) array)[length]) {
			length++;
		}
	}
	return length;
}




