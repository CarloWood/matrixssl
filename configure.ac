# Define package version here.
#
# CW_VERSION_MAJOR               : Increment when the whole library was rewritten; or some VERY MAJOR change was made.
# CW_VERSION_MINOR               : Increment when major changes have occured, like removing interfaces.
# CW_VERSION_REVISION            : Increment every public release; or set to 0 when CW_VERSION_MINOR was incremented.

define(CW_VERSION_MAJOR, 0)
define(CW_VERSION_MINOR, 0)
define(CW_VERSION_REVISION, 0)

# Package name and bug reporting.
define(CW_PACKAGE_NAME, [matrixssl])
define(CW_BUGREPORT, [carlo@alinoe.com])

# Version info, see http://www.gnu.org/software/libtool/manual.html#Updating-version-info
#
# CW_INTERFACE_VERSION           : Current interface version, increment whenever the interface is changed.
# CW_INTERFACE_VERSION_REVISION  : Revision, increment every public release; or set to 0 when the interface is changed.
# CW_INTERFACE_AGE               : Increment if interfaces have been added; or set to 0 when interfaces have been removed.

### Uncomment this if the project is a library.
define(CW_INTERFACE_VERSION, 0)
define(CW_INTERFACE_VERSION_REVISION, 0)
define(CW_INTERFACE_AGE, 0)

# CW_COMPILE_FLAGS may contain warning flags, but also default debug flags (-g*)
# and optimization flags (-O*) that which will be stripped when not required.
define(CW_COMPILE_FLAGS, [-W -Wall -Woverloaded-virtual -Wundef -Wpointer-arith -Wwrite-strings -Winline])
# CW_THREADS can be [no] (single-threaded), [yes] (multi-threaded) or [both] (single and multi-threaded applications).
define(CW_THREADS, [yes])
# CW_MAX_ERRORS is the maximum number of errors the compiler will show.
define(CW_MAX_ERRORS, 2)

dnl Package name and version
AC_INIT(CW_PACKAGE_NAME, CW_VERSION_MAJOR.CW_VERSION_MINOR.CW_VERSION_REVISION, CW_BUGREPORT)

dnl Automake options.
AM_INIT_AUTOMAKE(1.8.1 foreign subdir-objects)

dnl Minimum autoconf version to use.
AC_PREREQ(2.60)

dnl Where libtoolize should put it's macro files.
AC_CONFIG_MACRO_DIR([m4/aclocal])

dnl Put resulting configuration defines in this header file.
AC_CONFIG_HEADERS([config.h])

dnl Include maintainer mode targets
AM_MAINTAINER_MODE

dnl Check for compiler and preprocessor
AC_PROG_CC_C99
AC_PROG_CXX
AC_PROG_CXXCPP

dnl Substitute VERSIONINFO when CW_INTERFACE_VERSION is set.
# Libtool version info
VERSIONINFO="CW_INTERFACE_VERSION:CW_INTERFACE_VERSION_REVISION:CW_INTERFACE_AGE"
AC_SUBST(VERSIONINFO)

dnl Add --enable-debug (DEBUG, DOXYGEN_DEBUG), --enable-libcwd (CWDEBUG, DOXYGEN_CWDEBUG), --enable-optimize and --enable-profile options.
dnl Update USE_LIBCWD, LIBCWD(_R)_FLAGS, LIBCWD(_R)_LIBS and CXXFLAGS accordingly.
dnl Second parameter can be [no] (single-threaded), [yes] (multi-threaded) or [both] (single and multi-threaded applications).
dnl Third parameter can be empty (no limit), or an integer (larger than 0) to limit the maximum number of printed compiler errors.
CW_OPG_CXXFLAGS([CW_COMPILE_FLAGS], [CW_THREADS], [CW_MAX_ERRORS])

LT_INIT
LT_PREREQ([2.2])

dnl Checks for other programs.
AC_PROG_INSTALL

dnl Suppress warning from ar by supplying U flag.
dnl There seem to be two variants of AR[_]FLAGS in use, set both.
AC_SUBST(AR_FLAGS, [cruU])
AC_SUBST(ARFLAGS, [cruU])

dnl Check if we are the real maintainer.
cw_real_maintainer=0
if test -z "$MAINTAINER_MODE_TRUE" -a -n "$REPOBASE"; then
  if test "$(echo "$GIT_COMMITTER_EMAIL" | md5sum | cut -d \  -f 1)" = dnl
      "$(sed -n -e 's/.*MAINTAINER_HASH=//p' "$REPOBASE/autogen.sh")"; then
    cw_real_maintainer=1
  fi
fi
AM_CONDITIONAL(REAL_MAINTAINER, test $cw_real_maintainer = 1)

### Uncomment this if the project is using doxygen to generate documentation.
# We use doxygen for documentation.
#CW_DOXYGEN([])

### Uncomment this to add more configuration output files.
#AC_CONFIG_FILES([src/Makefile] [matrixssl.pc])

dnl Used to generate a makefile with includes without that automake sees an include.
dnl Instead of using include in the makefile.am, we use @matrixssl_include@.
matrixssl_include=include
AC_SUBST([matrixssl_include])

dnl The subdirectory of configs/ that should be used for the (standard) configuration files.
matrixssl_config_dir=default
AC_SUBST([matrixssl_config_dir])

dnl Flags that TU's must use that #include "matrixssl/matrixsslApi.h".
MATRIXSSL_CFLAGS='-maes -DMATRIX_CONFIGURATION_INCDIR_FIRST -I$(MATRIXSSL_BUILDDIR) -I$(MATRIXSSL_SRCDIR) -I$(MATRIXSSL_SRCDIR)/core/include -I$(MATRIXSSL_SRCDIR)/core/osdep/include'
MATRIXSSL_LIBS='$(MATRIXSSL_BUILDDIR)/matrixssl/libssl_s.la $(MATRIXSSL_BUILDDIR)/crypto/libcrypt_s.la $(MATRIXSSL_BUILDDIR)/core/libcore_s.la'

dnl In the case of this configure.ac being used, we could have used @top_srcdir@ and @top_builddir@
dnl instead of @matrixssl_srcdir@ and @matrixssl_builddir@. But when this library is build as a cwm4
dnl submodule then that would be substituted with the root of the main project and the build root of
dnl main project respectively, instead of the root of this (library) project; therefore we use
dnl @matrixssl_srcdir@ and @matrixssl_builddir@.
dnl
dnl In order to give those the right values when this configure.ac is being used (aka the configure
dnl script in this directory is being run) we can use the following variables.
matrixssl_srcdir="$ac_abs_confdir"
matrixssl_builddir="$ac_pwd"

AC_SUBST([matrixssl_srcdir])
AC_SUBST([matrixssl_builddir])
AC_SUBST([MATRIXSSL_CFLAGS])
AC_SUBST([MATRIXSSL_LIBS])

dnl Do not put AM_MAKEFLAGS as variable in automake.in.
AC_SUBST([AM_MAKEFLAGS])
AM_SUBST_NOTMAKE([AM_MAKEFLAGS])

AC_CONFIG_FILES([makefile core/makefile crypto/makefile crypto/GNUmakefile matrixssl/makefile
                matrixssl/GNUmakefile apps/makefile apps/common/GNUmakefile apps/common/makefile
                apps/dtls/GNUmakefile apps/dtls/makefile apps/ssl/GNUmakefile apps/ssl/makefile])
AC_OUTPUT
