AM_CPPFLAGS = \
	$(PROGRAM_CFLAGS) \
	-include $(CONFIG_HEADER)

BUILT_SOURCES = vala.stamp

bin_PROGRAMS = omap4-player-app

omap4_player_app_VALASOURCES = \
	player-app.gs \
	player-window.gs \
	playlist-control.gs

common_VALASOURCES = \
	$(top_srcdir)/common/video-area.gs \
	$(top_srcdir)/common/error-dialog.gs \
	$(top_srcdir)/common/application-window.gs \
	$(top_srcdir)/common/media-control.gs \
	$(top_srcdir)/common/defaults.gs

omap4_player_app_SOURCES = \
	$(omap4_player_app_VALASOURCES:.gs=.c) $(common_VALASOURCES:.gs=.c)

vala.stamp: $(omap4_player_app_VALASOURCES) $(common_VALASOURCES)
	$(VALAC) $(VALA_DEPS) -C  $^
	touch $@

omap4_player_app_LDADD = \
	$(PROGRAM_LIBS)

EXTRA_DIST = \
	$(omap4_player_app_VALASOURCES) \
	vala.stamp

DISTCLEANFILES =

