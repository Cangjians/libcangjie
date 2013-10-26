AC_PREREQ(2.63)
AC_INIT([libcangjie], [0.0.1], [https://github.com/Cangjians/libcangjie/issues], [libcangjie], [https://github.com/Cangjians/libcangjie])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([1.11 no-dist-gzip dist-xz tar-ustar foreign])
AC_PROG_MKDIR_P

m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

# Initialize libtool
LT_INIT([disable-static])

AC_MSG_CHECKING([whether to build with gcov testing])
AC_ARG_ENABLE([gcov],
              [AS_HELP_STRING([--enable-gcov],
                              [enable coverage testing (requires gcc and gcov)])],
              [],
              [enable_gcov=no])

AS_IF([test "x$enable_gcov" = "xyes" && test "x$GCC" = "xyes"],
      [
        GCOV_CFLAGS="$CFLAGS -fprofile-arcs -ftest-coverage"
        GCOV_LDFLAGS="$LDFLAGS -fprofile-arcs -ftest-coverage"
      ]
)

AM_CONDITIONAL([GCOV_ENABLED], [test "x$enable_gcov" = "xyes"])
AC_SUBST([GCOV_CFLAGS])
AC_SUBST([GCOV_LDFLAGS])
AC_MSG_RESULT([$enable_gcov])

PKG_CHECK_MODULES(sqlite3, [sqlite3])

# Define these substitions here to keep all version information in one place.
# For information on how to properly maintain the library version information,
# refer to the libtool manual, section "Updating library version information":
# http://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html
AC_SUBST([CANGJIE_SO_VERSION], [0:0:0])

# OUTPUT files
AC_CONFIG_FILES([
  Makefile
  data/cangjie.pc
])

AC_OUTPUT
