BEGIN {
  before_common_include=1
  reached_end=0
  verbatim=0

  # Write a header.
  printf "# This file is generated by gen_crypto_makefile_am.awk.\n# Any changes made here will be lost!\n# Added to the repository anyhow in order to make ./autogen.sh work.\n\n"
  printf "AM_CPPFLAGS =\n"
  printf "DEFS = -DMATRIX_CONFIGURATION_INCDIR_FIRST\n"
  printf "DEFAULT_INCLUDES = -I @matrixssl_srcdir@\n"
  printf "MATRIXSSL_SRCDIR = @matrixssl_srcdir@\n"
  printf "MATRIXSSL_BUILDDIR = @matrixssl_builddir@\n"
  printf "MATRIXSSL_ROOT = ..\n"
}

# Start processing the input file from this line (everything before this line is ignored).
/^MATRIXSSL_ROOT/ {
  before_common_include=0
  # We don't use it though.
  next
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
    # Truncate file.
    printf "# This file is generated by gen_crypto_makefile_am.awk!\n# All changes will be lost.\n# Added to the repository anyhow in order to make ./autogen.sh work.\n\n" > "crypto/makefile.inc"
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
  printf "# --------------- Maintainer's Section\n"
  printf "\nMAINTAINERCLEANFILES = $(srcdir)/makefile.in\n"
  printf "\nif MAINTAINER_MODE\n"
  printf "$(srcdir)/makefile.am: $(srcdir)/../gen_crypto_makefile_am.awk $(srcdir)/../generate_makefile_am.sh\n\t(cd $(srcdir)/.. && ./generate_makefile_am.sh)\n"
  printf "endif\n"
}
