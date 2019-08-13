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
        -I${top_builddir}/evio/matrixssl dnl
        -I${top_srcdir}/evio/matrixssl dnl
        -I${top_srcdir}/evio/matrixssl/core/include dnl
        -I${top_srcdir}/evio/matrixssl/core/osdep/include'

MATRIXSSL_LIBS='dnl
        ${top_builddir}/evio/matrixssl/matrixssl/libssl_s.la dnl
        ${top_builddir}/evio/matrixssl/core/libcore_s.la dnl
        ${top_builddir}/evio/matrixssl/crypto/crypt_s.la'

AC_SUBST([MATRIXSSL_CFLAGS])
AC_SUBST([MATRIXSSL_LIBS])

dnl Do not put AM_MAKEFLAGS as variable in automake.in.
AC_SUBST([AM_MAKEFLAGS])
AM_SUBST_NOTMAKE([AM_MAKEFLAGS])

dnl The makefiles to generate.
m4_if(cwm4_submodule_dirname, [], [m4_append_uniq([CW_SUBMODULE_SUBDIRS], cwm4_submodule_basename, [ ])])
m4_append_uniq([CW_SUBMODULE_CONFIG_FILES], cwm4_quote(cwm4_submodule_path[/makefile]), [ ])
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
