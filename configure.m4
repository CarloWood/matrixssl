dnl Used to generate a makefile with includes without that automake sees an include.
dnl Instead of using include in the makefile.am, we use @matrixssl_include@.
matrixssl_include=include
AC_SUBST([matrixssl_include])

dnl The subdirectory of configs/ that should be used for the (standard) configuration files.
matrixssl_config_dir=default
AC_SUBST([matrixssl_config_dir])

dnl Flags that TU's must use that #include "matrixssl/matrixsslApi.h".
MATRIXSSL_CFLAGS='dnl
        -maes dnl
        -DMATRIX_CONFIGURATION_INCDIR_FIRST dnl
        -I${top_builddir}/evio/protocol/matrixssl dnl
        -I${top_srcdir}/evio/protocol/matrixssl dnl
        -I${top_srcdir}/evio/protocol/matrixssl/core/include dnl
        -I${top_srcdir}/evio/protocol/matrixssl/core/osdep/include'

MATRIXSSL_LIBS='dnl
        ${top_builddir}/evio/protocol/matrixssl/matrixssl/libssl_s.la dnl
        ${top_builddir}/evio/protocol/matrixssl/crypto/libcrypt_s.la dnl
        ${top_builddir}/evio/protocol/matrixssl/core/libcore_s.la'

# We can use @top_srcdir@ and @top_builddir@ here because substitution
# isn't recursive and we need to use @matrixssl_srcdir@ and @matrixssl_builddir@
# to support building this as ExternalProject with cmake.
matrixssl_srcdir="$ac_abs_confdir/evio/protocol/matrixssl"
matrixssl_builddir="$ac_pwd/evio/protocol/matrixssl"

AC_SUBST([matrixssl_srcdir])
AC_SUBST([matrixssl_builddir])
AC_SUBST([MATRIXSSL_CFLAGS])
AC_SUBST([MATRIXSSL_LIBS])

dnl Do not put AM_MAKEFLAGS as variable in automake.in.
AC_SUBST([AM_MAKEFLAGS])
AM_SUBST_NOTMAKE([AM_MAKEFLAGS])

dnl The makefiles to generate.
m4_if(cwm4_submodule_dirname, [], [m4_append_uniq([CW_SUBMODULE_SUBDIRS], cwm4_submodule_basename, [ ])])
m4_append_uniq([CW_SUBMODULE_CONFIG_FILES], cwm4_quote(cwm4_submodule_path[/core/makefile]), [ ])
m4_append_uniq([CW_SUBMODULE_CONFIG_FILES], cwm4_quote(cwm4_submodule_path[/crypto/makefile]), [ ])
m4_append_uniq([CW_SUBMODULE_CONFIG_FILES], cwm4_quote(cwm4_submodule_path[/crypto/GNUmakefile]), [ ])
m4_append_uniq([CW_SUBMODULE_CONFIG_FILES], cwm4_quote(cwm4_submodule_path[/matrixssl/makefile]), [ ])
m4_append_uniq([CW_SUBMODULE_CONFIG_FILES], cwm4_quote(cwm4_submodule_path[/matrixssl/GNUmakefile]), [ ])
m4_append_uniq([CW_SUBMODULE_CONFIG_FILES], cwm4_quote(cwm4_submodule_path[/apps/makefile]), [ ])
m4_append_uniq([CW_SUBMODULE_CONFIG_FILES], cwm4_quote(cwm4_submodule_path[/apps/common/GNUmakefile]), [ ])
m4_append_uniq([CW_SUBMODULE_CONFIG_FILES], cwm4_quote(cwm4_submodule_path[/apps/common/makefile]), [ ])
m4_append_uniq([CW_SUBMODULE_CONFIG_FILES], cwm4_quote(cwm4_submodule_path[/apps/dtls/GNUmakefile]), [ ])
m4_append_uniq([CW_SUBMODULE_CONFIG_FILES], cwm4_quote(cwm4_submodule_path[/apps/dtls/makefile]), [ ])
m4_append_uniq([CW_SUBMODULE_CONFIG_FILES], cwm4_quote(cwm4_submodule_path[/apps/ssl/GNUmakefile]), [ ])
m4_append_uniq([CW_SUBMODULE_CONFIG_FILES], cwm4_quote(cwm4_submodule_path[/apps/ssl/makefile]), [ ])

dnl vim: filetype=config
