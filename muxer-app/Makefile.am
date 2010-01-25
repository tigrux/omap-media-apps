include $(top_srcdir)/common/common.am

BUILT_SOURCES = vala.stamp

bin_PROGRAMS = omap4-muxer-app

omap4_muxer_app_VALASOURCES = \
	muxer-app.gs \
	muxer-config.gs \
	muxer-control.gs \
	muxer-window.gs
	
omap4_muxer_app_SOURCES = \
	$(omap4_muxer_app_VALASOURCES:.gs=.c)

vala.stamp: $(omap4_muxer_app_VALASOURCES) $(COMMON_VAPI)
	$(VALAC) $(VALA_DEPS) -C  $^
	touch $@

omap4_muxer_app_LDADD = \
	$(PROGRAM_LIBS) $(COMMON_LIB)

desktopdir = $(datadir)/applications
desktop_DATA = omap4-muxer-app.desktop

pixmapsdir   = $(datadir)/pixmaps
pixmaps_DATA = omap4-muxer-app.png

EXTRA_DIST = \
	$(omap4_muxer_app_VALASOURCES) \
	vala.stamp \
	omap4-muxer-app.png \
	omap4-muxer-app.desktop \
	test.ini \
	test.xml

