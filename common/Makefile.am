all: vala.stamp

include common.am

vala.stamp: $(COMMON_VALASOURCES)
	$(VALAC) $(VALA_DEPS) -C -H common.h --library=common $^
	touch $@

commondir   = $(datadir)/omap4-apps
common_DATA = style.rc

EXTRA_DIST = \
	$(COMMON_VALASOURCES) \
	common.am \
	vala.stamp \
	common.vapi \
	common.h \
	style.rc

DISTCLEANFILES =

