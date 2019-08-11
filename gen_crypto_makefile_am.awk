BEGIN {
  before_common_include=1
  reached_end=0
  verbatim=0

  # Write a header.
  # Do not use the default includes.
  printf "AM_CPPFLAGS =\n"
  printf "DEFAULT_INCLUDES =\n"
}

# Start processing the input file from this line (everything before this line is ignored).
/^MATRIXSSL_ROOT/ {
  before_common_include=0
  # This is needed to include cryptoConfig.h
  $0 = "MATRIXSSL_ROOT:=$(abs_top_builddir)/evio/matrixssl"
}

# We're including this from GNUmakefile.am.
/^include.*common\.mk/ {
  next
}

# Copy this line and everything after it verbatim to the makefile.
/^SRC\+=/ {
  if (!verbatim)
  {
    verbatim=1
    printf "" > "crypto/makefile.inc"           # Truncate file.
  }
}

# Do not copy anything anymore once this line has been reached.
/^# Generated files/ {
  reached_end=1
}

/\.o:/ {
  if (verbatim)
    next
}

/`pwd`/ {
  gsub(/`pwd`/, "$(srcdir)")
}

# Write to stdout (or append to crypto/Makfile.inc for the verbatim part).
{
  if (!before_common_include && !reached_end)
  {
    if (verbatim)
      print >> "crypto/makefile.inc"
    else
      print
  }
}

END {
  # Write a trailer.

  printf "include makefile_ltlibs.inc\n\n"

  # Automatically generate makefile.am when gen_crypto_makefile_am.awk or generate_makefile_am.sh have been changed.
  printf "# --------------- Maintainer's Section\n\nif MAINTAINER_MODE\n"
  printf "$(srcdir)/makefile.am: $(srcdir)/../gen_crypto_makefile_am.awk $(srcdir)/../generate_makefile_am.sh\n\t(cd $(srcdir)/.. && ./generate_makefile_am.sh)\n"
  printf "endif\n"
}
