noinst_PROGRAMS = openclose date comment
openclose_SOURCES = openclose.c
openclose_CFLAGS = -I../src $(CFLAGS) $(GLIB_CFLAGS)
openclose_LDADD = $(top_builddir)/src/libvcd.la  $(GLIB_LIBS)

date_SOURCES = date.c
date_CFLAGS = -I../src $(CFLAGS) $(GLIB_CFLAGS)
date_LDADD = $(top_builddir)/src/libvcd.la $(GLIB_LIBS)

comment_SOURCES = comment.c
comment_CFLAGS = -I../src $(CFLAGS) $(GLIB_CFLAGS)
comment_LDADD = $(top_builddir)/src/libvcd.la $(GLIB_LIBS)

TESTS = openclose date comment

