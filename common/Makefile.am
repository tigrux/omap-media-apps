all: vala.stamp

include common.am

vala.stamp: $(COMMON_VALASOURCES)
	$(VALAC) $(VALA_DEPS) -C  $^
	touch $@

EXTRA_DIST = \
	$(COMMON_VALASOURCES) \
	common.am \
	vala.stamp

DISTCLEANFILES =

