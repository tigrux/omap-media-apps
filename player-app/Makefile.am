include $(top_srcdir)/common/common.am

BUILT_SOURCES = vala.stamp

bin_PROGRAMS = omap4-player-app

omap4_player_app_VALASOURCES = \
	player-app.gs \
	player-window.gs \
	playlist-control.gs

omap4_player_app_SOURCES = \
	$(omap4_player_app_VALASOURCES:.gs=.c)

vala.stamp: $(omap4_player_app_VALASOURCES) $(COMMON_VAPI)
	$(VALAC) $(VALA_DEPS) -C  $^
	touch $@

omap4_player_app_LDADD = \
	$(PROGRAM_LIBS) $(COMMON_LIB)

desktopdir = $(datadir)/applications
desktop_DATA = omap4-player-app.desktop

pixmapsdir   = $(datadir)/pixmaps
pixmaps_DATA = omap4-player-app.png

EXTRA_DIST = \
	$(omap4_player_app_VALASOURCES) \
	vala.stamp \
	omap4-player-app.png \
	omap4-player-app.desktop

