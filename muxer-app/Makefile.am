AM_CPPFLAGS = \
	$(PROGRAM_CFLAGS) \
	-include $(CONFIG_HEADER)

BUILT_SOURCES = vala.stamp

bin_PROGRAMS = omap4-muxer-app

omap4_muxer_app_VALASOURCES = \
	muxer-app.gs \
	muxer-config.gs \
	muxer-control.gs \
	muxer-window.gs
	
common_VALASOURCES = \
	$(top_srcdir)/common/video-area.gs \
	$(top_srcdir)/common/error-dialog.gs \
	$(top_srcdir)/common/media-window.gs \
	$(top_srcdir)/common/media-control.gs

omap4_muxer_app_SOURCES = \
	$(omap4_muxer_app_VALASOURCES:.gs=.c) $(common_VALASOURCES:.gs=.c)

vala.stamp: $(omap4_muxer_app_VALASOURCES) $(common_VALASOURCES)
	$(VALAC) $(VALA_DEPS) -C  $^
	touch $@

omap4_muxer_app_LDADD = \
	$(PROGRAM_LIBS)

EXTRA_DIST = \
	$(omap4_muxer_app_VALASOURCES) \
	vala.stamp \
	test.ini \
	test.xml

DISTCLEANFILES =

