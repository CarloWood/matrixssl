libtoolize --force --automake
aclocal -I m4/aclocal -I cwm4/aclocal
autoheader
automake --add-missing --foreign
autoconf && sed -i 's/rm -f core/rm -f/' configure
