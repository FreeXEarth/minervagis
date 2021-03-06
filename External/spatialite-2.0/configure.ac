#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT(spatialite, 2.0, a.furieri@lqt.it)
AC_LANG(C)

AM_INIT_AUTOMAKE
AM_MAINTAINER_MODE

# Checks for header files.
AC_CHECK_HEADERS(stdlib.h,, [AC_MSG_ERROR([cannot find stdlib.h, bailing out])])
AC_CHECK_HEADERS(stdio.h,, [AC_MSG_ERROR([cannot find stdio.h, bailing out])])
AC_CHECK_HEADERS(string.h,, [AC_MSG_ERROR([cannot find string.h, bailing out])])
AC_CHECK_HEADERS(memory.h,, [AC_MSG_ERROR([cannot find memory.h, bailing out])])
AC_CHECK_HEADERS(math.h,, [AC_MSG_ERROR([cannot find math.h, bailing out])])
AC_CHECK_HEADERS(float.h,, [AC_MSG_ERROR([cannot find float.h, bailing out])])
AC_CHECK_HEADERS(fcntl.h,, [AC_MSG_ERROR([cannot find fcntl.h, bailing out])])
AC_CHECK_HEADERS(inttypes.h,, [AC_MSG_ERROR([cannot find inttypes.h, bailing out])])
AC_CHECK_HEADERS(stddef.h,, [AC_MSG_ERROR([cannot find stddef.h, bailing out])])
AC_CHECK_HEADERS(stdint.h,, [AC_MSG_ERROR([cannot find stdint.h, bailing out])])
AC_CHECK_HEADERS(sys/time.h,, [AC_MSG_ERROR([cannot find sys/time.h, bailing out])])
AC_CHECK_HEADERS(unistd.h,, [AC_MSG_ERROR([cannot find unistd.h, bailing out])])


# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL
AM_PROG_LIBTOOL


# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_OFF_T
AC_TYPE_SIZE_T
AC_HEADER_TIME
AC_STRUCT_TM
AC_C_VOLATILE

# Checks for library functions.
AC_FUNC_LSTAT
AC_FUNC_LSTAT_FOLLOWS_SLASHED_SYMLINK
AC_FUNC_MEMCMP
AC_FUNC_STAT
AC_FUNC_STRFTIME
AC_CHECK_FUNCS([memset sqrt strcasecmp strerror strncasecmp strstr fdatasync ftruncate getcwd gettimeofday localtime_r memmove strerror])

AC_CONFIG_FILES([Makefile
		 src/Makefile
		 src/gaiageo/Makefile
		 src/spatialite/Makefile
		 src/shell/Makefile
		 src/headers/Makefile])

#-----------------------------------------------------------------------
#   --enable-geos
#
AC_ARG_ENABLE(geos, [AS_HELP_STRING(
  [--enable-geos], [enables GEOS inclusion [default=yes]])], 
  [], [geos=yes])
if test x"$enable_geos" != "xno"; then
  OMIT_GEOS_FLAGS=-DOMIT_GEOS=0
else
  OMIT_GEOS_FLAGS=-DOMIT_GEOS=1
fi
AC_SUBST(OMIT_GEOS_FLAGS)
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
#   --enable-proj
#
AC_ARG_ENABLE(proj, [AS_HELP_STRING(
  [--enable-proj], [enables PROJ.4 inclusion [default=yes]])], 
  [], [proj=yes])
if test x"$enable_proj" != "xno"; then
  OMIT_PROJ_FLAGS=-DOMIT_PROJ=0
else
  OMIT_PROJ_FLAGS=-DOMIT_PROJ=1
fi
AC_SUBST(OMIT_PROJ_FLAGS)
#-----------------------------------------------------------------------


# Checking for MinGW
AM_CONDITIONAL([MINGW], [test "$target_alias" = "mingw32"])

AC_OUTPUT
