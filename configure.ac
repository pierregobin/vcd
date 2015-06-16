AC_INIT([vcd],[0.0],[pierregobin@free.fr])
AC_PROG_CC
AC_PROG_RANLIB
AM_INIT_AUTOMAKE([1.9])
PKG_CHECK_MODULES([GLIB], [glib-2.0])
AC_SUBST([GLIB_LIBS])
AC_SUBST([GLIB_CFLAGS])
AC_CONFIG_FILES([Makefile src/Makefile test/Makefile])
AC_CONFIG_FILES([vcd.pc])
AC_OUTPUT

