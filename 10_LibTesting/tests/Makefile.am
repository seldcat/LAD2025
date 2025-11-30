AM_CPPFLAGS = -I$(top_srcdir)/src $(CHECK_CFLAGS)
AM_CFLAGS = --coverage
AM_LDFLAGS = --coverage

check_PROGRAMS = test_gmbuffer
test_gmbuffer_SOURCES = test_gmbuffer.c
test_gmbuffer_LDADD = ../src/libgmbuffer.la $(CHECK_LIBS)

TESTS = test_gmbuffer