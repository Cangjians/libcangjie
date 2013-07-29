AC_PREREQ(2.63)
AC_INIT([libcangjie2], [0.0.1], [TODO], [libcangjie2], [TODO])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([1.11 no-dist-gzip dist-xz tar-ustar foreign])
AC_PROG_MKDIR_P

m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

# Initialize libtool
LT_INIT([disable-static])

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
