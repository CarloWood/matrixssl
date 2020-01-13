include $(srcdir)/cwm4/root_makefile_top.am
AM_MAKEFLAGS = -I "$(srcdir)/core" -I "$(srcdir)/crypto" OBJS= STATIC=

SUBDIRS = core crypto matrixssl apps # @CW_SUBDIRS@

include $(srcdir)/cwm4/root_makefile_bottom.am

# --------------- Maintainer's Section

.PHONY: list-make-files list-configure-files
.SILENT:

# Delete these to make build dir 'clean'.
list-build-files: all
	@echo -e "apps/dtls/dtlsServer\napps/dtls/dtlsClient\napps/ssl/simpleServer\napps/ssl/server\napps/ssl/simpleClient\napps/ssl/client"
	@find "$(top_builddir)" -regextype egrep \( -name '.dirstamp' -o -regex '.*\.(lo|o|la|a)' \) -printf '%P\n'

# Delete these too to make build dir 'dist-clean'.
list-configure-files:
	@echo -e "Makefile\nconfig.h\nconfig.log\nconfig.status\nstamp-h1\nlibtool"
	@find "$(top_builddir)" -regextype egrep \( -name 'makefile' -o -name 'GNUmakefile' -o -regex '.*/\.deps/[^/]*\.(Plo|Po)' \) -printf '%P\n'
