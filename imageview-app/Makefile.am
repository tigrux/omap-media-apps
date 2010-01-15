AM_CPPFLAGS = \
	$(PROGRAM_CFLAGS) \
	-include $(CONFIG_HEADER)

BUILT_SOURCES = vala.stamp

VALA_DEPS = $$(for pkg in $(PROGRAM_MODULES); do echo --pkg $$pkg; done)

bin_PROGRAMS = omap4-imageview-app

omap4_imageview_app_VALASOURCES = \
	imageview-window.gs \
	imageview-app.gs \
	icon-list-control.gs

common_VALASOURCES = \
	$(top_srcdir)/common/video-area.gs \
	$(top_srcdir)/common/error-dialog.gs \
	$(top_srcdir)/common/utils.gs \
	$(top_srcdir)/common/defaults.gs

omap4_imageview_app_SOURCES = \
	$(omap4_imageview_app_VALASOURCES:.gs=.c) $(common_VALASOURCES:.gs=.c)

vala.stamp: $(omap4_imageview_app_VALASOURCES) $(common_VALASOURCES)
	$(VALAC) $(VALA_DEPS) -C  $^
	touch $@

omap4_imageview_app_LDADD = \
	$(PROGRAM_LIBS)

EXTRA_DIST = \
	$(omap4_imageview_app_VALASOURCES) \
	vala.stamp

DISTCLEANFILES =

