all: vala.stamp

VALASOURCES = \
	video-area.gs \
	error-dialog.gs \
	utils.gs \
	defaults.gs

SOURCES = \
	$(VALASOURCES:.gs=.c)

vala.stamp: $(VALASOURCES)
	$(VALAC) $(VALA_DEPS) -C  $^
	touch $@

EXTRA_DIST = \
	$(VALASOURCES) \
	vala.stamp

DISTCLEANFILES =

