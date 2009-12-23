AM_CPPFLAGS = \
	$(PROGRAM_CFLAGS) \
	-include $(CONFIG_HEADER)

BUILT_SOURCES = vala.stamp

VALA_DEPS = $$(for pkg in $(PROGRAM_MODULES); do echo --pkg $$pkg; done)

bin_PROGRAMS = omap4-player-app

omap4_player_app_VALASOURCES = \
	player-app.gs \
	player-window.gs \
	playlist-control.gs \
	$(top_srcdir)/common/video-area.gs

omap4_player_app_SOURCES = \
	$(omap4_player_app_VALASOURCES:.gs=.c)

vala.stamp: $(omap4_player_app_VALASOURCES)
	$(VALAC) $(VALA_DEPS) -C  $^
	touch $@

omap4_player_app_LDADD = \
	$(PROGRAM_LIBS)

EXTRA_DIST = \
	$(omap4_player_app_VALASOURCES) \
	vala.stamp

DISTCLEANFILES =

