bin_PROGRAMS = hello-greet

hello_greet_SOURCES = hello-greet.c
hello_greet_CPPFLAGS = -I$(top_srcdir)/lib -I$(top_builddir)
hello_greet_LDADD = $(top_builddir)/lib/libgreet.la

AM_CPPFLAGS = -D_GNU_SOURCE
