AC_INIT([rhasher], [1.0], [you@example.com])
AM_INIT_AUTOMAKE([foreign -Wall])
AC_PROG_CC
AC_CONFIG_MACRO_DIR([m4])

PKG_CHECK_MODULES([RHASH], [librhash], , [
  AC_MSG_ERROR([librhash is required])
])

AC_ARG_WITH([readline],
  AS_HELP_STRING([--with-readline], [enable readline support]),
  [], [with_readline=auto])

if test "x$with_readline" = "xno"; then
  have_readline=no
else
  PKG_CHECK_MODULES([READLINE], [readline], have_readline=yes, have_readline=no)
fi

if test "x$have_readline" = "xyes"; then
  AC_DEFINE([USE_READLINE], [1], [Use GNU Readline])
else
  READLINE_LIBS=""
  READLINE_CFLAGS=""
fi

AC_SUBST(READLINE_LIBS)
AC_SUBST(READLINE_CFLAGS)
AC_SUBST(RHASH_LIBS)

AC_OUTPUT([
Makefile
src/Makefile
tests/Makefile
])
