AC_PREREQ([2.69])
AC_INIT([guess100],[1.0],[bugs@example.invalid])
AM_INIT_AUTOMAKE([foreign subdir-objects -Wall])
AC_CONFIG_SRCDIR([src/guess100.c])
AC_CONFIG_HEADERS([config.h])

AC_PROG_CC

dnl --- gettext/i18n ---
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.21])

AC_DEFINE_UNQUOTED([LOCALEDIR], ["${localedir}"], [Locale directory])

AC_CONFIG_FILES([
  Makefile
  src/Makefile
  po/Makefile.in
])

AC_OUTPUT
