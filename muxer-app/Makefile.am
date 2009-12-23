AM_CFLAGS = -ansi

AM_CPPFLAGS = \
	$(PROGRAM_CFLAGS) \
	-include $(CONFIG_HEADER)

BUILT_SOURCES = vala.stamp

VALA_DEPS = $$(for pkg in $(PROGRAM_MODULES); do echo --pkg $$pkg; done)

bin_PROGRAMS = omap4-muxer-app

omap4_muxer_app_VALASOURCES = \
	muxer-app.gs \
	muxer-config.gs \
	muxer-control.gs \
	muxer-window.gs \
	$(top_srcdir)/common/video-area.gs

omap4_muxer_app_SOURCES = \
	$(omap4_muxer_app_VALASOURCES:.gs=.c)

vala.stamp: $(omap4_muxer_app_VALASOURCES)
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

