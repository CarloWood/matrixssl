BEGIN {
  reached_end=0
  before_common_include=1
  inside_addprefix=0

  # Write a header.
  printf "AM_CPPFLAGS =\n"
  printf "DEFS = -DMATRIX_CONFIGURATION_INCDIR_FIRST\n"
  printf "DEFAULT_INCLUDES = -I @top_builddir@/evio/matrixssl\n"

  printf "\nnoinst_LTLIBRARIES = libssl_s.la\n"
}

# Start processing the input file from this line (everything before this line is ignored).
/^MATRIXSSL_ROOT/ {
  before_common_include=0
  # We don't really use this, but well.
  $0 = "MATRIXSSL_ROOT := @top_srcdir@/evio/matrixssl"
}

# We're including this from GNUmakefile.in.
/^include.*common\.mk/ {
  next
}

/^SRC/ {
  sub(/^SRC *:= */, "libssl_s_la_SOURCES = ")
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
  printf "libssl_s_la_CFLAGS = $(CW_MATRIXSSL_CFLAGS)\n"

  # Automatically generate makefile.am when gen_matrixssl_makefile_am.awk or generate_makefile_am.sh have been changed.
  printf "\n# --------------- Maintainer's Section\n"
  printf "\nMAINTAINERCLEANFILES = $(srcdir)/makefile.in $(srcdir)/makefile.am\n"
  printf "\nif MAINTAINER_MODE\n"
  printf "$(srcdir)/makefile.am: $(srcdir)/../gen_matrixssl_makefile_am.awk $(srcdir)/../generate_makefile_am.sh\n\t(cd $(srcdir)/.. && ./generate_makefile_am.sh)\n"
  printf "endif\n"
}
