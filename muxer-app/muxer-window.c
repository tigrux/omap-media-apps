/* muxer-window.c generated by valac 0.10.0, the Vala compiler
 * generated from muxer-window.gs, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <common.h>
#include <gtk/gtk.h>
#include <gst/gst.h>
#include <gst/interfaces/xoverlay.h>


#define OMAP_TYPE_MUXER_WINDOW (omap_muxer_window_get_type ())
#define OMAP_MUXER_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), OMAP_TYPE_MUXER_WINDOW, OmapMuxerWindow))
#define OMAP_MUXER_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), OMAP_TYPE_MUXER_WINDOW, OmapMuxerWindowClass))
#define OMAP_IS_MUXER_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), OMAP_TYPE_MUXER_WINDOW))
#define OMAP_IS_MUXER_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), OMAP_TYPE_MUXER_WINDOW))
#define OMAP_MUXER_WINDOW_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), OMAP_TYPE_MUXER_WINDOW, OmapMuxerWindowClass))

typedef struct _OmapMuxerWindow OmapMuxerWindow;
typedef struct _OmapMuxerWindowClass OmapMuxerWindowClass;
typedef struct _OmapMuxerWindowPrivate OmapMuxerWindowPrivate;

#define OMAP_TYPE_MUXER_CONTROL (omap_muxer_control_get_type ())
#define OMAP_MUXER_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), OMAP_TYPE_MUXER_CONTROL, OmapMuxerControl))
#define OMAP_MUXER_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), OMAP_TYPE_MUXER_CONTROL, OmapMuxerControlClass))
#define OMAP_IS_MUXER_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), OMAP_TYPE_MUXER_CONTROL))
#define OMAP_IS_MUXER_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), OMAP_TYPE_MUXER_CONTROL))
#define OMAP_MUXER_CONTROL_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), OMAP_TYPE_MUXER_CONTROL, OmapMuxerControlClass))

typedef struct _OmapMuxerControl OmapMuxerControl;
typedef struct _OmapMuxerControlClass OmapMuxerControlClass;

#define OMAP_MUXER_WINDOW_TYPE_COMBO_COL (omap_muxer_window_combo_col_get_type ())
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_error_free0(var) ((var == NULL) ? NULL : (var = (g_error_free (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))
#define _g_key_file_free0(var) ((var == NULL) ? NULL : (var = (g_key_file_free (var), NULL)))

#define OMAP_TYPE_MUXER_CONFIG_PARSER (omap_muxer_config_parser_get_type ())
#define OMAP_MUXER_CONFIG_PARSER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), OMAP_TYPE_MUXER_CONFIG_PARSER, OmapMuxerConfigParser))
#define OMAP_MUXER_CONFIG_PARSER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), OMAP_TYPE_MUXER_CONFIG_PARSER, OmapMuxerConfigParserClass))
#define OMAP_IS_MUXER_CONFIG_PARSER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), OMAP_TYPE_MUXER_CONFIG_PARSER))
#define OMAP_IS_MUXER_CONFIG_PARSER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), OMAP_TYPE_MUXER_CONFIG_PARSER))
#define OMAP_MUXER_CONFIG_PARSER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), OMAP_TYPE_MUXER_CONFIG_PARSER, OmapMuxerConfigParserClass))

typedef struct _OmapMuxerConfigParser OmapMuxerConfigParser;
typedef struct _OmapMuxerConfigParserClass OmapMuxerConfigParserClass;

struct _OmapMuxerWindow {
	OmapMediaWindow parent_instance;
	OmapMuxerWindowPrivate * priv;
	GtkComboBox* combo_box;
	GtkListStore* combo_model;
	GtkFileChooserButton* chooser_button;
	GtkToolButton* preview_button;
	GtkToolButton* record_button;
	GtkToolButton* stop_button;
	OmapMuxerControl* muxer_control;
	OmapVideoArea* video_area;
	OmapDebugDialog* debug_dialog;
};

struct _OmapMuxerWindowClass {
	OmapMediaWindowClass parent_class;
};

typedef enum  {
	OMAP_MUXER_WINDOW_COMBO_COL_GROUP,
	OMAP_MUXER_WINDOW_COMBO_COL_PREVIEW,
	OMAP_MUXER_WINDOW_COMBO_COL_RECORD
} OmapMuxerWindowComboCol;


static gpointer omap_muxer_window_parent_class = NULL;

#define TITLE "Omap4 Muxer"
GType omap_muxer_window_get_type (void) G_GNUC_CONST;
GType omap_muxer_control_get_type (void) G_GNUC_CONST;
enum  {
	OMAP_MUXER_WINDOW_DUMMY_PROPERTY
};
GType omap_muxer_window_combo_col_get_type (void) G_GNUC_CONST;
void omap_muxer_window_setup_widgets (OmapMuxerWindow* self);
void omap_muxer_window_setup_toolbar (OmapMuxerWindow* self);
void omap_muxer_window_setup_notebook (OmapMuxerWindow* self);
void omap_muxer_window_on_chooser_file_set (OmapMuxerWindow* self);
static void _omap_muxer_window_on_chooser_file_set_gtk_file_chooser_button_file_set (GtkFileChooserButton* _sender, gpointer self);
void omap_muxer_window_on_preview (OmapMuxerWindow* self);
static void _omap_muxer_window_on_preview_gtk_tool_button_clicked (GtkToolButton* _sender, gpointer self);
void omap_muxer_window_on_pause (OmapMuxerWindow* self);
static void _omap_muxer_window_on_pause_gtk_tool_button_clicked (GtkToolButton* _sender, gpointer self);
void omap_muxer_window_on_record (OmapMuxerWindow* self);
static void _omap_muxer_window_on_record_gtk_tool_button_clicked (GtkToolButton* _sender, gpointer self);
void omap_muxer_window_on_stop (OmapMuxerWindow* self);
static void _omap_muxer_window_on_stop_gtk_tool_button_clicked (GtkToolButton* _sender, gpointer self);
void omap_muxer_window_setup_control (OmapMuxerWindow* self, const char* preview, const char* record);
OmapMuxerControl* omap_muxer_control_new (const char* preview, const char* record);
OmapMuxerControl* omap_muxer_control_construct (GType object_type, const char* preview, const char* record);
void omap_muxer_control_load (OmapMuxerControl* self, GError** error);
void omap_muxer_window_on_control_error (OmapMuxerWindow* self, GstObject* src, GError* _error_, const char* debug);
static void _omap_muxer_window_on_control_error_omap_media_control_error_message (OmapMediaControl* _sender, GstObject* src, GError* _error_, const char* debug, gpointer self);
void omap_muxer_window_on_preview_started (OmapMuxerWindow* self);
static void _omap_muxer_window_on_preview_started_omap_muxer_control_preview_started (OmapMuxerControl* _sender, gpointer self);
void omap_muxer_window_on_preview_stopped (OmapMuxerWindow* self);
static void _omap_muxer_window_on_preview_stopped_omap_muxer_control_preview_stopped (OmapMuxerControl* _sender, gpointer self);
void omap_muxer_window_on_record_started (OmapMuxerWindow* self);
static void _omap_muxer_window_on_record_started_omap_muxer_control_record_started (OmapMuxerControl* _sender, gpointer self);
void omap_muxer_window_on_record_stopped (OmapMuxerWindow* self);
static void _omap_muxer_window_on_record_stopped_omap_muxer_control_record_stopped (OmapMuxerControl* _sender, gpointer self);
void omap_muxer_window_on_prepared (OmapMuxerWindow* self, GstXOverlay* imagesink);
static void _omap_muxer_window_on_prepared_omap_media_control_prepare_xwindow_id (OmapMediaControl* _sender, GstXOverlay* imagesink, gpointer self);
gboolean omap_muxer_window_get_pipelines (OmapMuxerWindow* self, char** preview, char** record);
void omap_muxer_control_start_preview (OmapMuxerControl* self);
gboolean omap_muxer_control_get_previewing (OmapMuxerControl* self);
gboolean omap_muxer_control_get_recording (OmapMuxerControl* self);
void omap_muxer_control_start_record (OmapMuxerControl* self, GError** error);
void omap_muxer_control_stop_record (OmapMuxerControl* self);
void omap_muxer_control_stop_preview (OmapMuxerControl* self);
OmapMuxerConfigParser* omap_muxer_config_parser_new (void);
OmapMuxerConfigParser* omap_muxer_config_parser_construct (GType object_type);
GType omap_muxer_config_parser_get_type (void) G_GNUC_CONST;
gboolean omap_muxer_config_parser_parse_file (OmapMuxerConfigParser* self, const char* file, GKeyFile** key_file, GError** error);
void omap_muxer_control_stop (OmapMuxerControl* self);
void omap_muxer_window_show_debug (OmapMuxerWindow* self, GError* _error_, const char* debug);
void omap_muxer_window_setup_debug_dialog (OmapMuxerWindow* self);
void omap_muxer_window_on_debug_dialog_closed (OmapMuxerWindow* self);
static void _omap_muxer_window_on_debug_dialog_closed_omap_debug_dialog_closed (OmapDebugDialog* _sender, gpointer self);
OmapMuxerWindow* omap_muxer_window_new (void);
OmapMuxerWindow* omap_muxer_window_construct (GType object_type);
static GObject * omap_muxer_window_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static void omap_muxer_window_finalize (GObject* obj);
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);



GType omap_muxer_window_combo_col_get_type (void) {
	static volatile gsize omap_muxer_window_combo_col_type_id__volatile = 0;
	if (g_once_init_enter (&omap_muxer_window_combo_col_type_id__volatile)) {
		static const GEnumValue values[] = {{OMAP_MUXER_WINDOW_COMBO_COL_GROUP, "OMAP_MUXER_WINDOW_COMBO_COL_GROUP", "group"}, {OMAP_MUXER_WINDOW_COMBO_COL_PREVIEW, "OMAP_MUXER_WINDOW_COMBO_COL_PREVIEW", "preview"}, {OMAP_MUXER_WINDOW_COMBO_COL_RECORD, "OMAP_MUXER_WINDOW_COMBO_COL_RECORD", "record"}, {0, NULL, NULL}};
		GType omap_muxer_window_combo_col_type_id;
		omap_muxer_window_combo_col_type_id = g_enum_register_static ("OmapMuxerWindowComboCol", values);
		g_once_init_leave (&omap_muxer_window_combo_col_type_id__volatile, omap_muxer_window_combo_col_type_id);
	}
	return omap_muxer_window_combo_col_type_id__volatile;
}


void omap_muxer_window_setup_widgets (OmapMuxerWindow* self) {
	g_return_if_fail (self != NULL);
	gtk_window_set_title ((GtkWindow*) self, TITLE);
	omap_muxer_window_setup_toolbar (self);
	omap_muxer_window_setup_notebook (self);
	gtk_widget_show_all ((GtkWidget*) ((OmapMediaWindow*) self)->main_box);
	gtk_widget_realize ((GtkWidget*) self->video_area);
}


static void _omap_muxer_window_on_chooser_file_set_gtk_file_chooser_button_file_set (GtkFileChooserButton* _sender, gpointer self) {
	omap_muxer_window_on_chooser_file_set (self);
}


static void _omap_muxer_window_on_preview_gtk_tool_button_clicked (GtkToolButton* _sender, gpointer self) {
	omap_muxer_window_on_preview (self);
}


static void _omap_muxer_window_on_pause_gtk_tool_button_clicked (GtkToolButton* _sender, gpointer self) {
	omap_muxer_window_on_pause (self);
}


static void _omap_muxer_window_on_record_gtk_tool_button_clicked (GtkToolButton* _sender, gpointer self) {
	omap_muxer_window_on_record (self);
}


static void _omap_muxer_window_on_stop_gtk_tool_button_clicked (GtkToolButton* _sender, gpointer self) {
	omap_muxer_window_on_stop (self);
}


void omap_muxer_window_setup_toolbar (OmapMuxerWindow* self) {
	GtkToolItem* chooser_item;
	GtkFileChooserButton* _tmp0_;
	GtkFileFilter* file_filter;
	GtkToolItem* combo_item;
	GType s;
	GtkListStore* _tmp1_;
	GtkComboBox* _tmp2_;
	GtkCellRendererText* renderer;
	GtkToolButton* _tmp3_;
	GtkToolButton* pause_button;
	GtkToolButton* _tmp4_;
	GtkToolButton* _tmp5_;
	g_return_if_fail (self != NULL);
	chooser_item = g_object_ref_sink (gtk_tool_item_new ());
	gtk_container_add ((GtkContainer*) ((OmapMediaWindow*) self)->toolbar, (GtkWidget*) chooser_item);
	gtk_tool_item_set_expand (chooser_item, TRUE);
	self->chooser_button = (_tmp0_ = g_object_ref_sink ((GtkFileChooserButton*) gtk_file_chooser_button_new ("Config file", GTK_FILE_CHOOSER_ACTION_OPEN)), _g_object_unref0 (self->chooser_button), _tmp0_);
	gtk_container_add ((GtkContainer*) chooser_item, (GtkWidget*) self->chooser_button);
	g_signal_connect_object (self->chooser_button, "file-set", (GCallback) _omap_muxer_window_on_chooser_file_set_gtk_file_chooser_button_file_set, self, 0);
	file_filter = g_object_ref_sink (gtk_file_filter_new ());
	gtk_file_filter_set_name (file_filter, "Config files");
	gtk_file_filter_add_pattern (file_filter, "*.ini");
	gtk_file_filter_add_pattern (file_filter, "*.xml");
	gtk_file_chooser_add_filter ((GtkFileChooser*) self->chooser_button, file_filter);
	combo_item = g_object_ref_sink (gtk_tool_item_new ());
	gtk_container_add ((GtkContainer*) ((OmapMediaWindow*) self)->toolbar, (GtkWidget*) combo_item);
	s = G_TYPE_STRING;
	self->combo_model = (_tmp1_ = gtk_list_store_new (3, s, s, s), _g_object_unref0 (self->combo_model), _tmp1_);
	self->combo_box = (_tmp2_ = g_object_ref_sink ((GtkComboBox*) gtk_combo_box_new_with_model ((GtkTreeModel*) self->combo_model)), _g_object_unref0 (self->combo_box), _tmp2_);
	gtk_container_add ((GtkContainer*) combo_item, (GtkWidget*) self->combo_box);
	renderer = g_object_ref_sink ((GtkCellRendererText*) gtk_cell_renderer_text_new ());
	gtk_cell_layout_pack_start ((GtkCellLayout*) self->combo_box, (GtkCellRenderer*) renderer, TRUE);
	gtk_cell_layout_set_attributes ((GtkCellLayout*) self->combo_box, (GtkCellRenderer*) renderer, "text", OMAP_MUXER_WINDOW_COMBO_COL_GROUP, NULL, NULL);
	omap_media_window_toolbar_add_expander ((OmapMediaWindow*) self);
	self->preview_button = (_tmp3_ = g_object_ref_sink ((GtkToolButton*) gtk_tool_button_new_from_stock (GTK_STOCK_MEDIA_PLAY)), _g_object_unref0 (self->preview_button), _tmp3_);
	gtk_container_add ((GtkContainer*) ((OmapMediaWindow*) self)->toolbar, (GtkWidget*) self->preview_button);
	g_signal_connect_object (self->preview_button, "clicked", (GCallback) _omap_muxer_window_on_preview_gtk_tool_button_clicked, self, 0);
	pause_button = g_object_ref_sink ((GtkToolButton*) gtk_tool_button_new_from_stock (GTK_STOCK_MEDIA_PAUSE));
	gtk_container_add ((GtkContainer*) ((OmapMediaWindow*) self)->toolbar, (GtkWidget*) pause_button);
	g_signal_connect_object (pause_button, "clicked", (GCallback) _omap_muxer_window_on_pause_gtk_tool_button_clicked, self, 0);
	self->record_button = (_tmp4_ = g_object_ref_sink ((GtkToolButton*) gtk_tool_button_new_from_stock (GTK_STOCK_MEDIA_RECORD)), _g_object_unref0 (self->record_button), _tmp4_);
	gtk_container_add ((GtkContainer*) ((OmapMediaWindow*) self)->toolbar, (GtkWidget*) self->record_button);
	g_signal_connect_object (self->record_button, "clicked", (GCallback) _omap_muxer_window_on_record_gtk_tool_button_clicked, self, 0);
	self->stop_button = (_tmp5_ = g_object_ref_sink ((GtkToolButton*) gtk_tool_button_new_from_stock (GTK_STOCK_MEDIA_STOP)), _g_object_unref0 (self->stop_button), _tmp5_);
	gtk_container_add ((GtkContainer*) ((OmapMediaWindow*) self)->toolbar, (GtkWidget*) self->stop_button);
	g_signal_connect_object (self->stop_button, "clicked", (GCallback) _omap_muxer_window_on_stop_gtk_tool_button_clicked, self, 0);
	omap_media_window_toolbar_add_expander ((OmapMediaWindow*) self);
	omap_media_window_toolbar_add_quit_button ((OmapMediaWindow*) self);
	_g_object_unref0 (pause_button);
	_g_object_unref0 (renderer);
	_g_object_unref0 (combo_item);
	_g_object_unref0 (file_filter);
	_g_object_unref0 (chooser_item);
}


void omap_muxer_window_setup_notebook (OmapMuxerWindow* self) {
	OmapVideoArea* _tmp0_;
	GtkLabel* _tmp1_;
	g_return_if_fail (self != NULL);
	self->video_area = (_tmp0_ = g_object_ref_sink (omap_video_area_new ()), _g_object_unref0 (self->video_area), _tmp0_);
	gtk_notebook_append_page (((OmapMediaWindow*) self)->notebook, (GtkWidget*) self->video_area, (GtkWidget*) (_tmp1_ = g_object_ref_sink ((GtkLabel*) gtk_label_new ("Capture"))));
	_g_object_unref0 (_tmp1_);
}


static void _omap_muxer_window_on_control_error_omap_media_control_error_message (OmapMediaControl* _sender, GstObject* src, GError* _error_, const char* debug, gpointer self) {
	omap_muxer_window_on_control_error (self, src, _error_, debug);
}


static void _omap_muxer_window_on_preview_started_omap_muxer_control_preview_started (OmapMuxerControl* _sender, gpointer self) {
	omap_muxer_window_on_preview_started (self);
}


static void _omap_muxer_window_on_preview_stopped_omap_muxer_control_preview_stopped (OmapMuxerControl* _sender, gpointer self) {
	omap_muxer_window_on_preview_stopped (self);
}


static void _omap_muxer_window_on_record_started_omap_muxer_control_record_started (OmapMuxerControl* _sender, gpointer self) {
	omap_muxer_window_on_record_started (self);
}


static void _omap_muxer_window_on_record_stopped_omap_muxer_control_record_stopped (OmapMuxerControl* _sender, gpointer self) {
	omap_muxer_window_on_record_stopped (self);
}


static void _omap_muxer_window_on_prepared_omap_media_control_prepare_xwindow_id (OmapMediaControl* _sender, GstXOverlay* imagesink, gpointer self) {
	omap_muxer_window_on_prepared (self, imagesink);
}


void omap_muxer_window_setup_control (OmapMuxerWindow* self, const char* preview, const char* record) {
	OmapMuxerControl* _tmp0_;
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (preview != NULL);
	g_return_if_fail (record != NULL);
	self->muxer_control = (_tmp0_ = omap_muxer_control_new (preview, record), _g_object_unref0 (self->muxer_control), _tmp0_);
	{
		omap_muxer_control_load (self->muxer_control, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch0_g_error;
		}
	}
	goto __finally0;
	__catch0_g_error:
	{
		GError * e;
		e = _inner_error_;
		_inner_error_ = NULL;
		{
			OmapMuxerControl* _tmp1_;
			GtkMessageDialog* _tmp2_;
			self->muxer_control = (_tmp1_ = NULL, _g_object_unref0 (self->muxer_control), _tmp1_);
			_tmp2_ = omap_error_dialog (e);
			_g_object_unref0 (_tmp2_);
			_g_error_free0 (e);
			return;
		}
	}
	__finally0:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
	g_signal_connect_object ((OmapMediaControl*) self->muxer_control, "error-message", (GCallback) _omap_muxer_window_on_control_error_omap_media_control_error_message, self, 0);
	g_signal_connect_object (self->muxer_control, "preview-started", (GCallback) _omap_muxer_window_on_preview_started_omap_muxer_control_preview_started, self, 0);
	g_signal_connect_object (self->muxer_control, "preview-stopped", (GCallback) _omap_muxer_window_on_preview_stopped_omap_muxer_control_preview_stopped, self, 0);
	g_signal_connect_object (self->muxer_control, "record-started", (GCallback) _omap_muxer_window_on_record_started_omap_muxer_control_record_started, self, 0);
	g_signal_connect_object (self->muxer_control, "record-stopped", (GCallback) _omap_muxer_window_on_record_stopped_omap_muxer_control_record_stopped, self, 0);
	g_signal_connect_object ((OmapMediaControl*) self->muxer_control, "prepare-xwindow-id", (GCallback) _omap_muxer_window_on_prepared_omap_media_control_prepare_xwindow_id, self, 0);
}


void omap_muxer_window_on_prepared (OmapMuxerWindow* self, GstXOverlay* imagesink) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (imagesink != NULL);
	omap_video_area_set_sink (self->video_area, imagesink);
}


void omap_muxer_window_on_preview (OmapMuxerWindow* self) {
	g_return_if_fail (self != NULL);
	if (self->muxer_control == NULL) {
		char* preview;
		char* record;
		char* _tmp0_ = NULL;
		gboolean _tmp1_;
		char* _tmp2_;
		char* _tmp3_ = NULL;
		gboolean _tmp4_;
		char* _tmp5_;
		preview = NULL;
		record = NULL;
		if (!(_tmp4_ = (_tmp1_ = omap_muxer_window_get_pipelines (self, &_tmp0_, &_tmp3_), preview = (_tmp2_ = _tmp0_, _g_free0 (preview), _tmp2_), _tmp1_), record = (_tmp5_ = _tmp3_, _g_free0 (record), _tmp5_), _tmp4_)) {
			_g_free0 (record);
			_g_free0 (preview);
			return;
		}
		omap_muxer_window_setup_control (self, preview, record);
		_g_free0 (record);
		_g_free0 (preview);
	}
	if (self->muxer_control != NULL) {
		omap_muxer_control_start_preview (self->muxer_control);
	}
}


void omap_muxer_window_on_pause (OmapMuxerWindow* self) {
	g_return_if_fail (self != NULL);
	if (self->muxer_control == NULL) {
		return;
	}
	omap_media_control_set_state ((OmapMediaControl*) self->muxer_control, GST_STATE_PAUSED);
}


void omap_muxer_window_on_record (OmapMuxerWindow* self) {
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	if (self->muxer_control == NULL) {
		return;
	}
	if (!omap_muxer_control_get_previewing (self->muxer_control)) {
		return;
	}
	if (omap_muxer_control_get_recording (self->muxer_control)) {
		return;
	}
	{
		omap_muxer_control_start_record (self->muxer_control, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch1_g_error;
		}
	}
	goto __finally1;
	__catch1_g_error:
	{
		GError * e;
		e = _inner_error_;
		_inner_error_ = NULL;
		{
			GtkMessageDialog* _tmp0_;
			_tmp0_ = omap_error_dialog (e);
			_g_object_unref0 (_tmp0_);
			_g_error_free0 (e);
		}
	}
	__finally1:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
}


void omap_muxer_window_on_stop (OmapMuxerWindow* self) {
	g_return_if_fail (self != NULL);
	if (self->muxer_control == NULL) {
		return;
	}
	if (omap_muxer_control_get_recording (self->muxer_control)) {
		omap_muxer_control_stop_record (self->muxer_control);
	} else {
		if (omap_muxer_control_get_previewing (self->muxer_control)) {
			OmapMuxerControl* _tmp0_;
			omap_muxer_control_stop_preview (self->muxer_control);
			self->muxer_control = (_tmp0_ = NULL, _g_object_unref0 (self->muxer_control), _tmp0_);
		}
	}
}


void omap_muxer_window_on_chooser_file_set (OmapMuxerWindow* self) {
	char* config_file;
	GKeyFile* key_file;
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	config_file = gtk_file_chooser_get_filename ((GtkFileChooser*) self->chooser_button);
	key_file = g_key_file_new ();
	{
		if (g_str_has_suffix (config_file, ".ini")) {
			g_key_file_load_from_file (key_file, config_file, G_KEY_FILE_NONE, &_inner_error_);
			if (_inner_error_ != NULL) {
				if (_inner_error_->domain == G_FILE_ERROR) {
					goto __catch2_g_file_error;
				}
				if (_inner_error_->domain == G_KEY_FILE_ERROR) {
					goto __catch2_g_key_file_error;
				}
				if (_inner_error_->domain == G_MARKUP_ERROR) {
					goto __catch2_g_markup_error;
				}
				_g_key_file_free0 (key_file);
				_g_free0 (config_file);
				g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
				g_clear_error (&_inner_error_);
				return;
			}
		} else {
			OmapMuxerConfigParser* xml_parser;
			xml_parser = omap_muxer_config_parser_new ();
			omap_muxer_config_parser_parse_file (xml_parser, config_file, &key_file, &_inner_error_);
			if (_inner_error_ != NULL) {
				_g_object_unref0 (xml_parser);
				if (_inner_error_->domain == G_FILE_ERROR) {
					goto __catch2_g_file_error;
				}
				if (_inner_error_->domain == G_KEY_FILE_ERROR) {
					goto __catch2_g_key_file_error;
				}
				if (_inner_error_->domain == G_MARKUP_ERROR) {
					goto __catch2_g_markup_error;
				}
				_g_object_unref0 (xml_parser);
				_g_key_file_free0 (key_file);
				_g_free0 (config_file);
				g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
				g_clear_error (&_inner_error_);
				return;
			}
			_g_object_unref0 (xml_parser);
		}
	}
	goto __finally2;
	__catch2_g_file_error:
	{
		GError * e1;
		e1 = _inner_error_;
		_inner_error_ = NULL;
		{
			GtkMessageDialog* _tmp0_;
			_tmp0_ = omap_error_dialog (e1);
			_g_object_unref0 (_tmp0_);
			_g_error_free0 (e1);
			_g_key_file_free0 (key_file);
			_g_free0 (config_file);
			return;
		}
	}
	goto __finally2;
	__catch2_g_key_file_error:
	{
		GError * e2;
		e2 = _inner_error_;
		_inner_error_ = NULL;
		{
			GtkMessageDialog* _tmp1_;
			_tmp1_ = omap_error_dialog (e2);
			_g_object_unref0 (_tmp1_);
			_g_error_free0 (e2);
			_g_key_file_free0 (key_file);
			_g_free0 (config_file);
			return;
		}
	}
	goto __finally2;
	__catch2_g_markup_error:
	{
		GError * e3;
		e3 = _inner_error_;
		_inner_error_ = NULL;
		{
			GtkMessageDialog* _tmp2_;
			_tmp2_ = omap_error_dialog (e3);
			_g_object_unref0 (_tmp2_);
			_g_error_free0 (e3);
			_g_key_file_free0 (key_file);
			_g_free0 (config_file);
			return;
		}
	}
	__finally2:
	if (_inner_error_ != NULL) {
		_g_key_file_free0 (key_file);
		_g_free0 (config_file);
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
	{
		gtk_list_store_clear (self->combo_model);
		{
			gsize _tmp3_;
			char** group_collection;
			int group_collection_length1;
			int group_it;
			group_collection = g_key_file_get_groups (key_file, &_tmp3_);
			group_collection_length1 = _tmp3_;
			for (group_it = 0; group_it < _tmp3_; group_it = group_it + 1) {
				char* group;
				group = g_strdup (group_collection[group_it]);
				{
					char* preview;
					char* record;
					gboolean _tmp4_ = FALSE;
					preview = g_key_file_get_string (key_file, group, "preview", &_inner_error_);
					if (_inner_error_ != NULL) {
						_g_free0 (group);
						group_collection = (_vala_array_free (group_collection, group_collection_length1, (GDestroyNotify) g_free), NULL);
						if (_inner_error_->domain == G_KEY_FILE_ERROR) {
							goto __catch3_g_key_file_error;
						}
						_g_free0 (group);
						group_collection = (_vala_array_free (group_collection, group_collection_length1, (GDestroyNotify) g_free), NULL);
						_g_key_file_free0 (key_file);
						_g_free0 (config_file);
						g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
						g_clear_error (&_inner_error_);
						return;
					}
					record = g_key_file_get_string (key_file, group, "record", &_inner_error_);
					if (_inner_error_ != NULL) {
						_g_free0 (preview);
						_g_free0 (group);
						group_collection = (_vala_array_free (group_collection, group_collection_length1, (GDestroyNotify) g_free), NULL);
						if (_inner_error_->domain == G_KEY_FILE_ERROR) {
							goto __catch3_g_key_file_error;
						}
						_g_free0 (preview);
						_g_free0 (group);
						group_collection = (_vala_array_free (group_collection, group_collection_length1, (GDestroyNotify) g_free), NULL);
						_g_key_file_free0 (key_file);
						_g_free0 (config_file);
						g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
						g_clear_error (&_inner_error_);
						return;
					}
					if (preview == NULL) {
						_tmp4_ = TRUE;
					} else {
						_tmp4_ = record == NULL;
					}
					if (_tmp4_) {
						_g_free0 (record);
						_g_free0 (preview);
						_g_free0 (group);
						continue;
					}
					gtk_list_store_insert_with_values (self->combo_model, NULL, -1, OMAP_MUXER_WINDOW_COMBO_COL_GROUP, group, OMAP_MUXER_WINDOW_COMBO_COL_PREVIEW, preview, OMAP_MUXER_WINDOW_COMBO_COL_RECORD, record, -1, -1);
					_g_free0 (record);
					_g_free0 (preview);
					_g_free0 (group);
				}
			}
			group_collection = (_vala_array_free (group_collection, group_collection_length1, (GDestroyNotify) g_free), NULL);
		}
	}
	goto __finally3;
	__catch3_g_key_file_error:
	{
		GError * e4;
		e4 = _inner_error_;
		_inner_error_ = NULL;
		{
			GtkMessageDialog* _tmp5_;
			_tmp5_ = omap_error_dialog (e4);
			_g_object_unref0 (_tmp5_);
			_g_error_free0 (e4);
		}
	}
	__finally3:
	if (_inner_error_ != NULL) {
		_g_key_file_free0 (key_file);
		_g_free0 (config_file);
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
	_g_key_file_free0 (key_file);
	_g_free0 (config_file);
}


gboolean omap_muxer_window_get_pipelines (OmapMuxerWindow* self, char** preview, char** record) {
	gboolean result = FALSE;
	GtkTreeIter iter = {0};
	g_return_val_if_fail (self != NULL, FALSE);
	if (preview != NULL) {
		*preview = NULL;
	}
	if (record != NULL) {
		*record = NULL;
	}
	if (!gtk_combo_box_get_active_iter (self->combo_box, &iter)) {
		result = FALSE;
		return result;
	}
	gtk_tree_model_get ((GtkTreeModel*) self->combo_model, &iter, OMAP_MUXER_WINDOW_COMBO_COL_PREVIEW, preview, OMAP_MUXER_WINDOW_COMBO_COL_RECORD, record, -1, -1);
	result = TRUE;
	return result;
}


void omap_muxer_window_on_preview_started (OmapMuxerWindow* self) {
	g_return_if_fail (self != NULL);
	g_print ("preview started\n");
}


void omap_muxer_window_on_preview_stopped (OmapMuxerWindow* self) {
	g_return_if_fail (self != NULL);
	g_print ("preview stopped\n");
}


void omap_muxer_window_on_record_started (OmapMuxerWindow* self) {
	g_return_if_fail (self != NULL);
	g_print ("record started\n");
}


void omap_muxer_window_on_record_stopped (OmapMuxerWindow* self) {
	g_return_if_fail (self != NULL);
	g_print ("record stopped\n");
}


void omap_muxer_window_on_control_error (OmapMuxerWindow* self, GstObject* src, GError* _error_, const char* debug) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (src != NULL);
	g_return_if_fail (debug != NULL);
	omap_muxer_control_stop (self->muxer_control);
	omap_muxer_window_show_debug (self, _error_, debug);
}


void omap_muxer_window_show_debug (OmapMuxerWindow* self, GError* _error_, const char* debug) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (debug != NULL);
	omap_muxer_window_setup_debug_dialog (self);
	omap_debug_dialog_add_error_debug (self->debug_dialog, _error_, debug);
}


static void _omap_muxer_window_on_debug_dialog_closed_omap_debug_dialog_closed (OmapDebugDialog* _sender, gpointer self) {
	omap_muxer_window_on_debug_dialog_closed (self);
}


void omap_muxer_window_setup_debug_dialog (OmapMuxerWindow* self) {
	g_return_if_fail (self != NULL);
	if (self->debug_dialog == NULL) {
		OmapDebugDialog* _tmp0_;
		self->debug_dialog = (_tmp0_ = g_object_ref_sink (omap_debug_dialog_new ((GtkWindow*) self)), _g_object_unref0 (self->debug_dialog), _tmp0_);
		g_signal_connect_object (self->debug_dialog, "closed", (GCallback) _omap_muxer_window_on_debug_dialog_closed_omap_debug_dialog_closed, self, 0);
		gtk_widget_show_all ((GtkWidget*) self->debug_dialog);
	}
}


void omap_muxer_window_on_debug_dialog_closed (OmapMuxerWindow* self) {
	OmapMuxerControl* _tmp0_;
	OmapDebugDialog* _tmp1_;
	g_return_if_fail (self != NULL);
	self->muxer_control = (_tmp0_ = NULL, _g_object_unref0 (self->muxer_control), _tmp0_);
	self->debug_dialog = (_tmp1_ = NULL, _g_object_unref0 (self->debug_dialog), _tmp1_);
}


OmapMuxerWindow* omap_muxer_window_construct (GType object_type) {
	OmapMuxerWindow * self;
	self = (OmapMuxerWindow*) omap_media_window_construct (object_type);
	return self;
}


OmapMuxerWindow* omap_muxer_window_new (void) {
	return omap_muxer_window_construct (OMAP_TYPE_MUXER_WINDOW);
}


static GObject * omap_muxer_window_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GObjectClass * parent_class;
	OmapMuxerWindow * self;
	parent_class = G_OBJECT_CLASS (omap_muxer_window_parent_class);
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = OMAP_MUXER_WINDOW (obj);
	{
		omap_muxer_window_setup_widgets (self);
	}
	return obj;
}


static void omap_muxer_window_class_init (OmapMuxerWindowClass * klass) {
	omap_muxer_window_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->constructor = omap_muxer_window_constructor;
	G_OBJECT_CLASS (klass)->finalize = omap_muxer_window_finalize;
}


static void omap_muxer_window_instance_init (OmapMuxerWindow * self) {
}


static void omap_muxer_window_finalize (GObject* obj) {
	OmapMuxerWindow * self;
	self = OMAP_MUXER_WINDOW (obj);
	_g_object_unref0 (self->combo_box);
	_g_object_unref0 (self->combo_model);
	_g_object_unref0 (self->chooser_button);
	_g_object_unref0 (self->preview_button);
	_g_object_unref0 (self->record_button);
	_g_object_unref0 (self->stop_button);
	_g_object_unref0 (self->muxer_control);
	_g_object_unref0 (self->video_area);
	_g_object_unref0 (self->debug_dialog);
	G_OBJECT_CLASS (omap_muxer_window_parent_class)->finalize (obj);
}


GType omap_muxer_window_get_type (void) {
	static volatile gsize omap_muxer_window_type_id__volatile = 0;
	if (g_once_init_enter (&omap_muxer_window_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (OmapMuxerWindowClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) omap_muxer_window_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (OmapMuxerWindow), 0, (GInstanceInitFunc) omap_muxer_window_instance_init, NULL };
		GType omap_muxer_window_type_id;
		omap_muxer_window_type_id = g_type_register_static (OMAP_TYPE_MEDIA_WINDOW, "OmapMuxerWindow", &g_define_type_info, 0);
		g_once_init_leave (&omap_muxer_window_type_id__volatile, omap_muxer_window_type_id);
	}
	return omap_muxer_window_type_id__volatile;
}


static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	if ((array != NULL) && (destroy_func != NULL)) {
		int i;
		for (i = 0; i < array_length; i = i + 1) {
			if (((gpointer*) array)[i] != NULL) {
				destroy_func (((gpointer*) array)[i]);
			}
		}
	}
}


static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	_vala_array_destroy (array, array_length, destroy_func);
	g_free (array);
}




