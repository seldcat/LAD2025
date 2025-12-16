AC_PREREQ([2.69])

dnl ============================================================
dnl  Project metadata
dnl ============================================================
AC_INIT(
  [hello-greet],              dnl package name
  [1.0],                      dnl version
  [bugs@example.invalid]      dnl bug report address
)

AM_INIT_AUTOMAKE(
  [foreign subdir-objects -Wall dist-xz]
)

AC_CONFIG_SRCDIR([src/hello-greet.c])
AC_CONFIG_HEADERS([config.h])

AM_SILENT_RULES([yes])

dnl ============================================================
dnl  Toolchain
dnl ============================================================
AC_PROG_CC
LT_INIT                   dnl libtool (shared libraries)

dnl ============================================================
dnl  gettext / i18n
dnl ============================================================
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.21])

dnl LOCALEDIR will be used in code
AC_DEFINE_UNQUOTED(
  [LOCALEDIR],
  ["${localedir}"],
  [System locale directory]
)

dnl ============================================================
dnl  Checks for headers / functions (minimal but real)
dnl ============================================================
AC_CHECK_HEADERS([stdlib.h string.h locale.h])
AC_CHECK_FUNCS([setlocale getenv])

dnl ============================================================
dnl  Output files
dnl ============================================================
AC_CONFIG_FILES([
  Makefile
  lib/Makefile
  src/Makefile
  tests/Makefile
  man/Makefile
  po/Makefile.in
  doc/Makefile
])

AC_OUTPUT
