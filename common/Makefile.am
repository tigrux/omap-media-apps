all: libcommon.a

include common.am

BUILT_SOURCES = vala.stamp

vala.stamp: $(libcommon_a_VALASOURCES)
	$(VALAC) $(VALA_DEPS) -C -H common.h --library=common $^
	touch $@

commondir   = $(datadir)/omap4-apps
common_DATA = style.rc

noinst_LIBRARIES = libcommon.a

libcommon_a_VALASOURCES = \
	video-area.gs \
	error-dialog.gs \
	media-window.gs \
	media-control.gs

libcommon_a_SOURCES = \
	$(libcommon_a_VALASOURCES:.gs=.c)

EXTRA_DIST = \
	$(libcommon_a_VALASOURCES) \
	common.am \
	vala.stamp \
	common.vapi \
	common.h \
	style.rc

