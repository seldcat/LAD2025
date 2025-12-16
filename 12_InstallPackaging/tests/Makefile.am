check_PROGRAMS = test_greet test_i18n
TESTS = test_greet test_i18n

test_greet_SOURCES = test_greet.c
test_greet_CPPFLAGS = -I$(top_srcdir)/lib -I$(top_builddir)
test_greet_LDADD = $(top_builddir)/lib/libgreet.la

TESTS_ENVIRONMENT = APP_LOCALEDIR="$(top_builddir)/po"

test_greet_CPPFLAGS += -DTESTING


