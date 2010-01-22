/* common.h generated by valac, the Vala compiler, do not modify */


#ifndef __COMMON_H__
#define __COMMON_H__

#include <glib.h>
#include <gtk/gtk.h>
#include <gst/interfaces/xoverlay.h>
#include <stdlib.h>
#include <string.h>
#include <glib-object.h>
#include <gst/gst.h>

G_BEGIN_DECLS


#define TYPE_VIDEO_AREA (video_area_get_type ())
#define VIDEO_AREA(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_VIDEO_AREA, VideoArea))
#define VIDEO_AREA_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_VIDEO_AREA, VideoAreaClass))
#define IS_VIDEO_AREA(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_VIDEO_AREA))
#define IS_VIDEO_AREA_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_VIDEO_AREA))
#define VIDEO_AREA_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_VIDEO_AREA, VideoAreaClass))

typedef struct _VideoArea VideoArea;
typedef struct _VideoAreaClass VideoAreaClass;
typedef struct _VideoAreaPrivate VideoAreaPrivate;

#define TYPE_DEBUG_DIALOG (debug_dialog_get_type ())
#define DEBUG_DIALOG(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_DEBUG_DIALOG, DebugDialog))
#define DEBUG_DIALOG_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_DEBUG_DIALOG, DebugDialogClass))
#define IS_DEBUG_DIALOG(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_DEBUG_DIALOG))
#define IS_DEBUG_DIALOG_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_DEBUG_DIALOG))
#define DEBUG_DIALOG_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_DEBUG_DIALOG, DebugDialogClass))

typedef struct _DebugDialog DebugDialog;
typedef struct _DebugDialogClass DebugDialogClass;
typedef struct _DebugDialogPrivate DebugDialogPrivate;

#define TYPE_MEDIA_WINDOW (media_window_get_type ())
#define MEDIA_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_MEDIA_WINDOW, MediaWindow))
#define MEDIA_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_MEDIA_WINDOW, MediaWindowClass))
#define IS_MEDIA_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_MEDIA_WINDOW))
#define IS_MEDIA_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_MEDIA_WINDOW))
#define MEDIA_WINDOW_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_MEDIA_WINDOW, MediaWindowClass))

typedef struct _MediaWindow MediaWindow;
typedef struct _MediaWindowClass MediaWindowClass;
typedef struct _MediaWindowPrivate MediaWindowPrivate;

#define MEDIA_WINDOW_TYPE_TAB (media_window_tab_get_type ())

#define TYPE_MEDIA_CONTROL (media_control_get_type ())
#define MEDIA_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_MEDIA_CONTROL, MediaControl))
#define MEDIA_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_MEDIA_CONTROL, MediaControlClass))
#define IS_MEDIA_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_MEDIA_CONTROL))
#define IS_MEDIA_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_MEDIA_CONTROL))
#define MEDIA_CONTROL_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_MEDIA_CONTROL, MediaControlClass))

typedef struct _MediaControl MediaControl;
typedef struct _MediaControlClass MediaControlClass;
typedef struct _MediaControlPrivate MediaControlPrivate;

struct _VideoArea {
	GtkDrawingArea parent_instance;
	VideoAreaPrivate * priv;
	guint32 xid;
};

struct _VideoAreaClass {
	GtkDrawingAreaClass parent_class;
};

struct _DebugDialog {
	GtkDialog parent_instance;
	DebugDialogPrivate * priv;
	GtkTextBuffer* text_buffer;
	gint errors_n;
};

struct _DebugDialogClass {
	GtkDialogClass parent_class;
};

struct _MediaWindow {
	GtkWindow parent_instance;
	MediaWindowPrivate * priv;
	GtkNotebook* notebook;
	GtkToolbar* toolbar;
	GtkVBox* main_box;
	gboolean is_fullscreen;
};

struct _MediaWindowClass {
	GtkWindowClass parent_class;
};

typedef enum  {
	MEDIA_WINDOW_TAB_LIST,
	MEDIA_WINDOW_TAB_VIDEO
} MediaWindowTab;

struct _MediaControl {
	GObject parent_instance;
	MediaControlPrivate * priv;
};

struct _MediaControlClass {
	GObjectClass parent_class;
};


GType video_area_get_type (void);
VideoArea* video_area_new (void);
VideoArea* video_area_construct (GType object_type);
GstXOverlay* video_area_get_sink (VideoArea* self);
void video_area_set_sink (VideoArea* self, GstXOverlay* value);
GType debug_dialog_get_type (void);
DebugDialog* debug_dialog_new (GtkWindow* parent);
DebugDialog* debug_dialog_construct (GType object_type, GtkWindow* parent);
void debug_dialog_add_error_debug (DebugDialog* self, GError* _error_, const char* debug);
void debug_dialog_text_insert_new_line (DebugDialog* self, GtkTextIter* iter);
GtkBox* debug_dialog_new_error_box (DebugDialog* self);
void error_dialog (GError* _error_);
GType media_window_get_type (void);
GType media_window_tab_get_type (void);
extern gboolean media_window_style_applied;
gboolean media_window_apply_style (void);
void media_window_lookup_and_set_icon_name (MediaWindow* self, const char* name);
void media_window_toolbar_add_quit_button (MediaWindow* self);
void media_window_toolbar_add_expander (MediaWindow* self);
void media_window_toggle_fullscreen (MediaWindow* self);
void media_window_set_fullscreen (MediaWindow* self, gboolean value);
void media_window_on_quit (MediaWindow* self);
gboolean media_window_quit (MediaWindow* self);
MediaWindow* media_window_new (void);
MediaWindow* media_window_construct (GType object_type);
GType media_control_get_type (void);
extern GQuark media_control_prepare_xwindow_q;
void media_control_remove_signals (MediaControl* self);
void media_control_add_signals (MediaControl* self);
void media_control_on_bus_message (MediaControl* self, GstMessage* message);
void media_control_on_bus_sync_message (MediaControl* self, GstMessage* message);
MediaControl* media_control_new (void);
MediaControl* media_control_construct (GType object_type);
GstBin* media_control_get_pipeline (MediaControl* self);
void media_control_set_pipeline (MediaControl* self, GstBin* value);
GstState media_control_get_state (MediaControl* self);
void media_control_set_state (MediaControl* self, GstState value);
gint64 media_control_get_position (MediaControl* self);
void media_control_set_position (MediaControl* self, gint64 value);
gint64 media_control_get_duration (MediaControl* self);


G_END_DECLS

#endif
