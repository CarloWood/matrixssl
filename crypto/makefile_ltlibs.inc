noinst_LTLIBRARIES = libcrypt_s.la libcrypto_default.la libaes_aesni.la libchacha20poly.la libchacha20poly_sse2.la libchacha20poly_avx2.la libchacha20poly_ssse3.la libcurve25519.la libed25519.la

CW_STANDARD_CFLAGS = $(C_STD) $(CFLAGS_ENABLE_AES) $(CFLAGS_GARBAGE_COLLECTION) $(CFLAGS_OMIT_FRAMEPOINTER) -I$(MATRIXSSL_ROOT)

libcrypto_default_la_SOURCES = \
        common/alg_info.c common/digest_info.c symmetric/aes.c symmetric/aesCBC.c symmetric/aesGCM.c \
        symmetric/arc4.c symmetric/des3.c symmetric/idea.c symmetric/rc2.c symmetric/seed.c digest/hash.c \
        digest/sha256_standalone.c digest/sha1.c digest/sha256.c digest/sha512.c digest/md5sha1.c digest/md5.c \
        digest/hmac.c digest/md4.c digest/md2.c digest/hkdf.c keyformat/asn1.c keyformat/asn1fmt.c keyformat/base64.c \
        keyformat/crl.c keyformat/pem_decode_mem.c keyformat/pem_decode_file.c keyformat/pkcs.c keyformat/x509.c \
        layer/matrix.c math/pstm.c math/pstmnt.c math/pstm_montgomery_reduce.c math/pstm_mul_comba.c  \
        math/pstm_sqr_comba.c prng/prng.c prng/yarrow.c pubkey/dh.c pubkey/dh_params.c pubkey/dh_export.c \
        pubkey/dh_import.c pubkey/dh_gen_key.c pubkey/dh_gen_secret.c pubkey/dh_import_priv.c pubkey/ecc.c \
        pubkey/ecc_curve.c pubkey/ecc_curve_data.c pubkey/ecc_curve_config.c pubkey/ecc_math.c pubkey/ecc_priv.c \
        pubkey/ecc_priv_el_gamal.c pubkey/ecc_pub.c pubkey/ecc_keygen.c pubkey/ecc_gen_shared.c pubkey/ecc_parse_file.c \
        pubkey/ecc_parse_mem.c pubkey/ecc_write_mem.c pubkey/ecc_write_file.c pubkey/ecc_export.c pubkey/ecc_import.c \
        pubkey/pubkey.c pubkey/pubkey_sign.c pubkey/pubkey_verify.c pubkey/pubkey_parse_mem.c pubkey/pubkey_parse_file.c \
        pubkey/rsa.c pubkey/rsa_priv.c pubkey/rsa_pub.c pubkey/rsa_keygen.c pubkey/rsa_parse_mem.c pubkey/rsa_parse_file.c \
        pubkey/rsa_write_mem.c pubkey/rsa_write_file.c scalarmult/ps_x25519.c crypto_sign/ps_ed25519.c
libcrypto_default_la_CFLAGS = $(CFLAGS_CORE_INCLUDE) $(OPT) $(CW_STANDARD_CFLAGS)

libaes_aesni_la_SOURCES = symmetric/aes_aesni.c
libaes_aesni_la_CFLAGS = $(CFLAGS_ENABLE_AESNI) $(CFLAGS_CORE_INCLUDE) $(OPT) $(CW_STANDARD_CFLAGS)

libchacha20poly_la_SOURCES = \
        aead/chacha20poly1305ietf/donna/poly1305_donna.c aead/chacha20poly1305ietf/ref/chacha20_ref.c \
        aead/chacha20poly1305ietf/stream_chacha20.c aead/chacha20poly1305ietf/onetimeauth_poly1305.c \
        aead/chacha20poly1305ietf/ps_chacha20poly1305ietf.c aead/chacha20poly1305ietf/aead_chacha20poly1305.c \
        aead/chacha20poly1305ietf/utils.c aead/chacha20poly1305ietf/verify.c aead/chacha20poly1305ietf/runtime.c 
libchacha20poly_la_CFLAGS = $(CFLAGS_ADDITIONAL_CHACHA20POLY) $(CFLAGS_CORE_INCLUDE) $(OPT_CHACHA20POLY) $(CW_STANDARD_CFLAGS)

libchacha20poly_sse2_la_SOURCES = aead/chacha20poly1305ietf/sse2/poly1305_sse2.c
libchacha20poly_sse2_la_CFLAGS = $(CFLAGS_ADDITIONAL_CHACHA20POLY) $(CFLAGS_ENABLE_SSE2) $(CFLAGS_CORE_INCLUDE) $(OPT_CHACHA20POLY) $(CW_STANDARD_CFLAGS)

libchacha20poly_avx2_la_SOURCES = aead/chacha20poly1305ietf/dolbeau/chacha20_dolbeau-avx2.c
libchacha20poly_avx2_la_CFLAGS = $(CFLAGS_ADDITIONAL_CHACHA20POLY) $(CFLAGS_ENABLE_AVX2) $(CFLAGS_CORE_INCLUDE) $(OPT_CHACHA20POLY) $(CW_STANDARD_CFLAGS)

libchacha20poly_ssse3_la_SOURCES = aead/chacha20poly1305ietf/dolbeau/chacha20_dolbeau-ssse3.c
libchacha20poly_ssse3_la_CFLAGS = $(CFLAGS_ADDITIONAL_CHACHA20POLY) $(CFLAGS_ENABLE_SSSE3) $(CFLAGS_CORE_INCLUDE) $(OPT_CHACHA20POLY) $(CW_STANDARD_CFLAGS)

libcurve25519_la_SOURCES = \
        scalarmult/curve25519/scalarmult_curve25519.c scalarmult/curve25519/ref10/x25519_ref10.c \
        scalarmult/ed25519/ref10/scalarmult_ed25519_ref10.c scalarmult/crypto_scalarmult.c \
        scalarmult/crypto_core/ed25519/core_ed25519.c scalarmult/crypto_core/ed25519/ref10/ed25519_ref10.c 
libcurve25519_la_CFLAGS = $(CFLAGS_ADDITIONAL_X25519) $(CFLAGS_CORE_INCLUDE) $(OPT) $(CW_STANDARD_CFLAGS)

libed25519_la_SOURCES = crypto_sign/crypto_sign.c crypto_sign/ed25519/ref10/sign.c crypto_sign/ed25519/ref10/open.c
libed25519_la_CFLAGS = $(CFLAGS_ADDITIONAL_ED25519) $(CFLAGS_CORE_INCLUDE) $(OPT) $(CW_STANDARD_CFLAGS)

libcrypt_s_la_SOURCES =
libcrypt_s_la_LIBADD = libcrypto_default.la libaes_aesni.la libchacha20poly.la libchacha20poly_sse2.la libchacha20poly_avx2.la libchacha20poly_ssse3.la libcurve25519.la libed25519.la
