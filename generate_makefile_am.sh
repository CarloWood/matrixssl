#! /bin/bash

awk -b -f gen_core_makefile_am.awk core/GNUmakefile > core/makefile.am
awk -b -f gen_crypto_makefile_am.awk crypto/Makefile > crypto/makefile.am
awk -b -f gen_matrixssl_makefile_am.awk matrixssl/Makefile > matrixssl/makefile.am
