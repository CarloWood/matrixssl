## Overview

This fork adds support for GNU autotools, for building `matrixssl` as a libtool library,
and so it can be build in a build-directory rather than the source directory.

The advantage of having the library as `libmatrix.la` is that it can then be linked
into a shared library-- for example-- or used within another autotool-based project,
as git submodule.

Currently the (only) project that is doing this is [evio](https://github.com/CarloWood/evio)
which is git submodule itself (and under development) relying on [cwm4](https://github.com/CarloWood/cwm4)
for its inclusion into the application project. Adding direct support for `cwm4` to this
`matrixssl` submodule is on the `TODO` list.

## Upstream README

![MatrixSSL Banner](img/matrixssl_logo_transparent_md.png)

Lightweight Embedded SSL/TLS Implementation
*Official source repository of matrixssl.org*

![license](https://img.shields.io/badge/License-GPL-blue.svg)
[releases](https://github.com/matrixssl/matrixssl/releases)

## Features

+ Small total footprint with crypto provider
+ SSL 3.0 and TLS 1.0, 1.1, 1.2 and 1.3 server and client support
+ Included crypto library - RSA, ECC, AES, 3DES, ARC4, SHA1, SHA256, MD5, ChaCha20-Poly1305
+ Assembly language optimizations for Intel, ARM and MIPS
+ Session re-keying and cipher renegotiation
+ Full support for session resumption/caching
+ Server Name Indication and Stateless Session Tickets
+ RFC7301 Application Protocol Negotiation
+ Server and client X.509 certificate chain authentication
+ Client authentication with an external security token
+ Parsing of X.509 .pem and ASN.1 DER certificate formats
+ PKCS#1.5, PKCS#5 PKCS#8 and PKCS#12 support for key formatting
+ RSASSA-PSS Signature Algorithm support
+ Certificate Revocation List (CRL) support
+ Fully cross platform, portable codebase; minimum use of system calls
+ Pluggable cipher suite interface
+ Pluggable crypto provider interface
+ Pluggable operating system and malloc interface
+ TCP/IP optional
+ Multithreading optional
+ Only a handful of external APIs, all non-blocking
+ Example client and server code included
+ Clean, heavily commented code in portable C
+ User and developer documentation
