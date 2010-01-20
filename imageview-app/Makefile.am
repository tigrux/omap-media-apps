include $(top_srcdir)/common/common.am

AM_CPPFLAGS = \
	$(PROGRAM_CFLAGS) \
	-include $(CONFIG_HEADER)

BUILT_SOURCES = vala.stamp

bin_PROGRAMS = omap4-imageview-app

omap4_imageview_app_VALASOURCES = \
	imageview-window.gs \
	imageview-app.gs \
	iconlist-control.gs \
	image-control.gs

omap4_imageview_app_SOURCES = \
	$(omap4_imageview_app_VALASOURCES:.gs=.c) $(COMMON_SOURCES)

vala.stamp: $(omap4_imageview_app_VALASOURCES) $(COMMON_VALASOURCES)
	$(VALAC) $(VALA_DEPS) -C  $^
	touch $@

omap4_imageview_app_LDADD = \
	$(PROGRAM_LIBS)

EXTRA_DIST = \
	$(omap4_imageview_app_VALASOURCES) \
	vala.stamp

DISTCLEANFILES =

