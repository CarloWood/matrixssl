BEGIN {
  reached_end=0
  before_common_include=1
  inside_addprefix=0

  # Write a header.
  # Do not use the default includes.
  printf "AM_CPPFLAGS =\n"
  printf "DEFAULT_INCLUDES =\n"
}

# Start processing the input file from this line (everything before this line is ignored).
/^MATRIXSSL_ROOT/ {
  before_common_include=0
  # This is needed to include matrixsslConfig.h
  $0 = "MATRIXSSL_ROOT:=$(abs_top_builddir)/evio/matrixssl"
}

# We're including this from GNUmakefile.am.
/^include.*common\.mk/ {
  next
}

# Do not copy anything anymore once this line has been reached.
/^# Generated files/ {
  reached_end=1
}

# Write result to stdout.
{
  if (!reached_end && !before_common_include)
    print
}

END {
  # Write a trailer.
  printf "noinst_LTLIBRARIES = libssl_s.la\n"
  printf "libssl_s_la_SOURCES = $(SRC)\n"
  printf "libssl_s_la_CFLAGS = $(MATRIXSSL_CFLAGS) $(CFLAGS_POSITION_INDEPENDENT) $(CFLAGS_GARBAGE_COLLECTION)\n"

  # Automatically generate makefile.am when gen_matrixssl_makefile_am.awk or generate_makefile_am.sh have been changed.
  printf "# --------------- Maintainer's Section\n\nif MAINTAINER_MODE\n"
  printf "$(srcdir)/makefile.am: $(srcdir)/../gen_matrixssl_makefile_am.awk $(srcdir)/../generate_makefile_am.sh\n\t(cd $(srcdir)/.. && ./generate_makefile_am.sh)\n"
  printf "endif\n"
}
