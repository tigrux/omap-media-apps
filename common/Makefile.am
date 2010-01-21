all: vala.stamp

include common.am

vala.stamp: $(COMMON_VALASOURCES)
	$(VALAC) $(VALA_DEPS) -C $^
	touch $@

commondir   = $(datadir)/omap4-apps
common_DATA = style.rc

EXTRA_DIST = \
	$(COMMON_VALASOURCES) \
	common.am \
	vala.stamp \
	style.rc

DISTCLEANFILES =

