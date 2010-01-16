all: vala.stamp

VALASOURCES = \
	video-area.gs \
	error-dialog.gs \
	utils.gs \
	defaults.gs

SOURCES = \
	$(VALASOURCES:.gs=.c)

VALA_DEPS = $$(for pkg in $(PROGRAM_MODULES); do echo --pkg $$pkg; done)

vala.stamp: $(VALASOURCES)
	$(VALAC) $(VALA_DEPS) -C  $^
	touch $@

EXTRA_DIST = \
	$(VALASOURCES) \
	vala.stamp

DISTCLEANFILES =

