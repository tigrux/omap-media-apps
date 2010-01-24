/* common.vapi generated by valac, do not modify. */

[CCode (cprefix = "Omap", lower_case_cprefix = "omap_")]
namespace Omap {
	[CCode (cheader_filename = "common.h")]
	public class DebugDialog : Gtk.Dialog {
		public int errors_n;
		public Gtk.TextBuffer text_buffer;
		public DebugDialog (Gtk.Window parent);
		public void add_error_debug (GLib.Error error, string debug);
		public Gtk.Box new_error_box ();
		public void text_insert_new_line (ref Gtk.TextIter iter);
		public signal void closed ();
	}
	[CCode (cheader_filename = "common.h")]
	public class MediaControl : GLib.Object {
		public static GLib.Quark prepare_xwindow_q;
		public Gst.XOverlay xoverlay;
		public MediaControl ();
		public void add_signals ();
		public void on_bus_message (Gst.Message message);
		public void on_bus_sync_message (Gst.Message message);
		public void remove_signals ();
		public void tag_foreach_func (Gst.TagList tag_list, string tag_name);
		public int64 duration { get; }
		public Gst.Bin pipeline { get; set; }
		public int64 position { get; set; }
		public Gst.State state { get; set; }
		public signal void element_message (Gst.Object src, Gst.Structure structure);
		public signal void eos_message (Gst.Object src);
		public signal void error_message (Gst.Object src, GLib.Error error, string debug);
		public signal void prepare_xwindow_id (Gst.XOverlay imagesink);
		public signal void segment_done_message (Gst.Object src, Gst.Format format, int64 pos);
		public signal void segment_start_message (Gst.Object src, Gst.Format format, int64 pos);
		public signal void state_changed_message (Gst.Object src, Gst.State old, Gst.State current, Gst.State pending);
		public signal void tag_found (string name, GLib.Value tag_value);
		public signal void tag_message (Gst.Object src, Gst.TagList tag_list);
	}
	[CCode (cheader_filename = "common.h")]
	public class MediaWindow : Gtk.Window {
		[CCode (cprefix = "OMAP_MEDIA_WINDOW_TAB_", cheader_filename = "common.h")]
		public enum Tab {
			LIST,
			VIDEO
		}
		public bool is_fullscreen;
		public Gtk.VBox main_box;
		public Gtk.Notebook notebook;
		public static bool style_applied;
		public Gtk.Toolbar toolbar;
		public MediaWindow ();
		public static bool apply_style ();
		public void lookup_and_set_icon_name (string name);
		public void on_quit ();
		public bool quit ();
		public void toggle_fullscreen ();
		public void toolbar_add_expander ();
		public void toolbar_add_quit_button ();
		public bool fullscreen { get; set; }
	}
	[CCode (cheader_filename = "common.h")]
	public class VideoArea : Gtk.DrawingArea {
		public uint32 xid;
		public VideoArea ();
		public override bool button_press_event (Gdk.EventButton event);
		public override bool expose_event (Gdk.EventExpose e);
		public Gst.XOverlay sink { get; set; }
		public signal void activated ();
	}
}
[CCode (cheader_filename = "common.h")]
public static void error_dialog (GLib.Error error);
