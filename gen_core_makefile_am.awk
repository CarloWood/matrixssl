BEGIN {
  outside_ifeq=1
  inside_addprefix=0
  constructing_sources=0

  # Write a header.
  # Do not use the default includes.
  printf "AM_CPPFLAGS =\n"
  printf "DEFAULT_INCLUDES =\n"
}

# Stop processing after this line.
/^else/ { outside_ifeq=1 }

# Let awk do the functionality of 'addprefix' because automake can't.
/\$\(addprefix/ {
  inside_addprefix=1
  addprefix=""
  sub(/_s_a_/, "_s_la_")
  lead=gensub(/ *=.*/, "", 1)
  prefix=gensub(/.*\(addprefix */, "", 1)
  prefix=gensub(/,.*/, "", 1, prefix)
  sub(/^.*\(addprefix *[^,]*, */, "")
}

/\\$/ {
  if (inside_addprefix)
  {
    sub(/\\$/, "")
    addprefix=addprefix $0
    next
  }
}

{
  if (inside_addprefix)
  {
    inside_addprefix=0
    sub(/ *\) *$/, "")
    addprefix=addprefix $0
    printf "%s =", lead
    split(addprefix ,a, / */, seps);
    for (key in a) { printf " %s%s", prefix, a[key] }
    printf "\n"
    next
  }
}

# Let awk do the substituation for $(OSDEP) because automake can't.
/^OSDEP=/ {
  sub(/OSDEP=/, "")
  osdep_str=$0
  next
}

# Construct libcore_s_la_SOURCES directly from SRC_CORE.
/^(VPATH|libcore_s_a_SOURCES)/ {
  next
}

{
  if (constructing_sources)
  {
    if ($0 == "")
    {
      constructing_sources=0
      print sources
      print "libcore_s_la_LIBADD = libsfzutf_s.la libtestsupp_s.la"
    }
    else
    {
      $0 = gensub(/^[[:space:]]*([^[:space:]\\]*)[[:space:]\\]*$/, " \\1", 1)
      sub(/\$\(OSDEP\)/, osdep_str)
      if ($0 !~ /^ osdep/)
        sub(/^ /, " src/")
      sources=sources $0
      next
    }
  }
}

/^SRC_CORE *=/ {
  constructing_sources=1
  sources=""
  sub(/^SRC_CORE/, "libcore_s_la_SOURCES")
}

# Fix variables names that contain "_s_a_".
/_s_a_/ {
  sub(/=/, " = ")
  sub(/_s_a_/, "_s_la_")
}

# Fix lines that start with noinst_LIBRARIES to use libtool.
/^noinst_LIBRARIES/ {
  sub(/^noinst_LIBRARIES/, "noinst_LTLIBRARIES")
  sub(/=/, " = ")
  gsub(/\.a/, ".la")
}

# Stop automake from interpreting 'include' keywords.
/^include/ {
  sub(/^include/, "@matrixssl_include@")
}

/^libcore_s_la_CFLAGS/ {
  sub(/=/, "= $(core_API_CFLAGS)")
}

/^libsfzutf_s_la_CFLAGS/ {
  sub(/=/, "= $(core_API_CFLAGS) $(sfzutf_API_CFLAGS)")
}

/^libtestsupp_s_la_CFLAGS/ {
  sub(/=/, "= $(core_API_CFLAGS) $(testsupp_API_CFLAGS)")
}

# Write result to stdout.
{
  if (!outside_ifeq)
    print
}

# Start processing after this line.
/^ifeq/ { outside_ifeq=0 }

END {
  # Write a trailer.

  # Print all makefile variables.
  printf "\nprint:\n\t@$(foreach V,$(sort $(.VARIABLES)), $(if $(filter-out environment%% default automatic, $(origin $V)),$(warning $V=$($V) ($(value $V)))))\n\n"

  # Automatically generate makefile.am when gen_core_makefile_am.awk or generate_makefile_am.sh have been changed.
  printf "# --------------- Maintainer's Section\n\nif MAINTAINER_MODE\n"
  printf "$(srcdir)/makefile.am: $(srcdir)/../gen_core_makefile_am.awk $(srcdir)/../generate_makefile_am.sh\n\t(cd $(srcdir)/.. && ./generate_makefile_am.sh)\n"
  printf "endif\n"
}
