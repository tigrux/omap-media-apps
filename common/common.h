/* common.h generated by valac, the Vala compiler, do not modify */


#ifndef __COMMON_H__
#define __COMMON_H__

#include <glib.h>
#include <gtk/gtk.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <X11/Xregion.h>
#include <gst/interfaces/xoverlay.h>
#include <stdlib.h>
#include <string.h>
#include <glib-object.h>
#include <gst/gst.h>

G_BEGIN_DECLS


#define OMAP_TYPE_VIDEO_AREA (omap_video_area_get_type ())
#define OMAP_VIDEO_AREA(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), OMAP_TYPE_VIDEO_AREA, OmapVideoArea))
#define OMAP_VIDEO_AREA_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), OMAP_TYPE_VIDEO_AREA, OmapVideoAreaClass))
#define OMAP_IS_VIDEO_AREA(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), OMAP_TYPE_VIDEO_AREA))
#define OMAP_IS_VIDEO_AREA_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), OMAP_TYPE_VIDEO_AREA))
#define OMAP_VIDEO_AREA_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), OMAP_TYPE_VIDEO_AREA, OmapVideoAreaClass))

typedef struct _OmapVideoArea OmapVideoArea;
typedef struct _OmapVideoAreaClass OmapVideoAreaClass;
typedef struct _OmapVideoAreaPrivate OmapVideoAreaPrivate;

#define OMAP_TYPE_DEBUG_DIALOG (omap_debug_dialog_get_type ())
#define OMAP_DEBUG_DIALOG(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), OMAP_TYPE_DEBUG_DIALOG, OmapDebugDialog))
#define OMAP_DEBUG_DIALOG_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), OMAP_TYPE_DEBUG_DIALOG, OmapDebugDialogClass))
#define OMAP_IS_DEBUG_DIALOG(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), OMAP_TYPE_DEBUG_DIALOG))
#define OMAP_IS_DEBUG_DIALOG_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), OMAP_TYPE_DEBUG_DIALOG))
#define OMAP_DEBUG_DIALOG_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), OMAP_TYPE_DEBUG_DIALOG, OmapDebugDialogClass))

typedef struct _OmapDebugDialog OmapDebugDialog;
typedef struct _OmapDebugDialogClass OmapDebugDialogClass;
typedef struct _OmapDebugDialogPrivate OmapDebugDialogPrivate;

#define OMAP_TYPE_ERROR_DIALOG (omap_error_dialog_get_type ())
#define OMAP_ERROR_DIALOG(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), OMAP_TYPE_ERROR_DIALOG, OmapErrorDialog))
#define OMAP_ERROR_DIALOG_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), OMAP_TYPE_ERROR_DIALOG, OmapErrorDialogClass))
#define OMAP_IS_ERROR_DIALOG(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), OMAP_TYPE_ERROR_DIALOG))
#define OMAP_IS_ERROR_DIALOG_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), OMAP_TYPE_ERROR_DIALOG))
#define OMAP_ERROR_DIALOG_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), OMAP_TYPE_ERROR_DIALOG, OmapErrorDialogClass))

typedef struct _OmapErrorDialog OmapErrorDialog;
typedef struct _OmapErrorDialogClass OmapErrorDialogClass;
typedef struct _OmapErrorDialogPrivate OmapErrorDialogPrivate;

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

#define OMAP_TYPE_MEDIA_CONTROL (omap_media_control_get_type ())
#define OMAP_MEDIA_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), OMAP_TYPE_MEDIA_CONTROL, OmapMediaControl))
#define OMAP_MEDIA_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), OMAP_TYPE_MEDIA_CONTROL, OmapMediaControlClass))
#define OMAP_IS_MEDIA_CONTROL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), OMAP_TYPE_MEDIA_CONTROL))
#define OMAP_IS_MEDIA_CONTROL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), OMAP_TYPE_MEDIA_CONTROL))
#define OMAP_MEDIA_CONTROL_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), OMAP_TYPE_MEDIA_CONTROL, OmapMediaControlClass))

typedef struct _OmapMediaControl OmapMediaControl;
typedef struct _OmapMediaControlClass OmapMediaControlClass;
typedef struct _OmapMediaControlPrivate OmapMediaControlPrivate;

struct _OmapVideoArea {
	GtkDrawingArea parent_instance;
	OmapVideoAreaPrivate * priv;
	XID xid;
};

struct _OmapVideoAreaClass {
	GtkDrawingAreaClass parent_class;
};

struct _OmapDebugDialog {
	GtkDialog parent_instance;
	OmapDebugDialogPrivate * priv;
	GtkTextBuffer* text_buffer;
	gint errors_n;
};

struct _OmapDebugDialogClass {
	GtkDialogClass parent_class;
};

struct _OmapErrorDialog {
	GtkMessageDialog parent_instance;
	OmapErrorDialogPrivate * priv;
};

struct _OmapErrorDialogClass {
	GtkMessageDialogClass parent_class;
};

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

struct _OmapMediaControl {
	GObject parent_instance;
	OmapMediaControlPrivate * priv;
	GstXOverlay* xoverlay;
};

struct _OmapMediaControlClass {
	GObjectClass parent_class;
};


GType omap_video_area_get_type (void);
OmapVideoArea* omap_video_area_new (void);
OmapVideoArea* omap_video_area_construct (GType object_type);
GstXOverlay* omap_video_area_get_sink (OmapVideoArea* self);
void omap_video_area_set_sink (OmapVideoArea* self, GstXOverlay* value);
GType omap_debug_dialog_get_type (void);
OmapDebugDialog* omap_debug_dialog_new (GtkWindow* parent);
OmapDebugDialog* omap_debug_dialog_construct (GType object_type, GtkWindow* parent);
void omap_debug_dialog_add_error_debug (OmapDebugDialog* self, GError* _error_, const char* debug);
void omap_debug_dialog_text_insert_new_line (OmapDebugDialog* self, GtkTextIter* iter);
GtkBox* omap_debug_dialog_new_error_box (OmapDebugDialog* self);
GType omap_error_dialog_get_type (void);
OmapErrorDialog* omap_error_dialog_new (GError* e);
OmapErrorDialog* omap_error_dialog_construct (GType object_type, GError* e);
GtkMessageDialog* omap_error_dialog (GError* e);
GType omap_media_window_get_type (void);
GType omap_media_window_tab_get_type (void);
extern gboolean omap_media_window_style_applied;
gboolean omap_media_window_apply_style (void);
void omap_media_window_lookup_and_set_icon_name (OmapMediaWindow* self, const char* name);
void omap_media_window_toolbar_add_quit_button (OmapMediaWindow* self);
void omap_media_window_toolbar_add_expander (OmapMediaWindow* self);
void omap_media_window_toggle_fullscreen (OmapMediaWindow* self);
void omap_media_window_on_quit (OmapMediaWindow* self);
gboolean omap_media_window_quit (OmapMediaWindow* self);
OmapMediaWindow* omap_media_window_new (void);
OmapMediaWindow* omap_media_window_construct (GType object_type);
gboolean omap_media_window_get_fullscreen (OmapMediaWindow* self);
void omap_media_window_set_fullscreen (OmapMediaWindow* self, gboolean value);
GType omap_media_control_get_type (void);
extern GQuark omap_media_control_prepare_xwindow_q;
void omap_media_control_remove_signals (OmapMediaControl* self);
void omap_media_control_add_signals (OmapMediaControl* self);
void omap_media_control_on_bus_message (OmapMediaControl* self, GstMessage* message);
void omap_media_control_tag_foreach_func (OmapMediaControl* self, GstTagList* tag_list, const char* tag_name);
void omap_media_control_on_bus_sync_message (OmapMediaControl* self, GstMessage* message);
OmapMediaControl* omap_media_control_new (void);
OmapMediaControl* omap_media_control_construct (GType object_type);
GstBin* omap_media_control_get_pipeline (OmapMediaControl* self);
void omap_media_control_set_pipeline (OmapMediaControl* self, GstBin* value);
GstState omap_media_control_get_state (OmapMediaControl* self);
void omap_media_control_set_state (OmapMediaControl* self, GstState value);
gint64 omap_media_control_get_position (OmapMediaControl* self);
void omap_media_control_set_position (OmapMediaControl* self, gint64 value);
gint64 omap_media_control_get_duration (OmapMediaControl* self);


G_END_DECLS

#endif
