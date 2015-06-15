noinst_PROGRAMS = openclose date comment var dumpvar
openclose_SOURCES = openclose.c
openclose_CFLAGS = -I../src $(CFLAGS) $(GLIB_CFLAGS)
openclose_LDADD = $(top_builddir)/src/libvcd.a  $(GLIB_LIBS)

date_SOURCES = date.c
date_CFLAGS = -I../src $(CFLAGS) $(GLIB_CFLAGS)
date_LDADD = $(top_builddir)/src/libvcd.a $(GLIB_LIBS)

comment_SOURCES = comment.c
comment_CFLAGS = -I../src $(CFLAGS) $(GLIB_CFLAGS)
comment_LDADD = $(top_builddir)/src/libvcd.a $(GLIB_LIBS)

var_SOURCES = var.c
var_CFLAGS = -I../src $(CFLAGS) $(GLIB_CFLAGS)
var_LDADD = $(top_builddir)/src/libvcd.a $(GLIB_LIBS)

dumpvar_SOURCES = dumpvar.c
dumpvar_CFLAGS = -I../src $(CFLAGS) $(GLIB_CFLAGS)
dumpvar_LDADD = $(top_builddir)/src/libvcd.a $(GLIB_LIBS)

TESTS = openclose date comment var dumpvar

