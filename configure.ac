AC_INIT([omap4-media-apps], [0.2.1], [tigrux@gmail.com], [omap4-media-apps])
AC_CONFIG_SRCDIR([Makefile.am])
AC_CONFIG_HEADERS(config.h)
AM_INIT_AUTOMAKE([foreign])

AC_PROG_CC
AC_PROG_LIBTOOL
AC_DISABLE_STATIC

AC_PATH_PROG(VALAC, valac, valac)
AC_SUBST(VALAC)

AC_SUBST(CFLAGS)
AC_SUBST(CPPFLAGS)
AC_SUBST(LDFLAGS)

VALA_DEPS="--pkg gtk+-2.0 --pkg gdk-x11-2.0 --pkg gstreamer-0.10 --pkg gstreamer-interfaces-0.10"
AC_SUBST(VALA_DEPS)

min_gtk_ver=2.14
min_gst_ver=0.10

PKG_CHECK_MODULES(PROGRAM, 
    gtk+-2.0 >= $min_gtk_ver
    gdk-x11-2.0 >= $min_gtk_ver
    gstreamer-0.10 >= $min_gst_ver
    gstreamer-interfaces-0.10 >= $min_gst_ver
    )
AC_SUBST(PROGRAM_CFLAGS)
AC_SUBST(PROGRAM_LIBS)

AC_CONFIG_FILES([
	Makefile
	common/Makefile
	player-app/Makefile
	muxer-app/Makefile
	imageview-app/Makefile
	])

AC_OUTPUT

