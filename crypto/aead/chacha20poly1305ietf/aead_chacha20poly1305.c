#include "ps_chacha20poly1305ietf_config.h"
#ifdef USE_MATRIX_CHACHA20_POLY1305_IETF
# include "osdep_stdint.h"
# include "osdep_stdlib.h"
# include "osdep_limits.h"
# include "osdep_string.h"

# include "crypto_aead_chacha20poly1305.h"
# include "crypto_onetimeauth_poly1305.h"
# include "crypto_stream_chacha20.h"
# include "crypto_verify_16.h"
# ifdef USE_MATRIX_CHACHA20_POLY1305_IETF_KEYGEN
# include "randombytes.h"
# endif /* USE_MATRIX_CHACHA20_POLY1305_IETF_KEYGEN */
# include "utils.h"

# include "private/common.h"

static const unsigned char _pad0[16] = { 0 };

int
psCrypto_aead_chacha20poly1305_encrypt_detached(unsigned char *c,
                                              unsigned char *mac,
                                              unsigned long long *maclen_p,
                                              const unsigned char *m,
                                              unsigned long long mlen,
                                              const unsigned char *ad,
                                              unsigned long long adlen,
                                              const unsigned char *nsec,
                                              const unsigned char *npub,
                                              const unsigned char *k)
{
    crypto_onetimeauth_poly1305_state state;
    unsigned char                     block0[64U];
    unsigned char                     slen[8U];

    (void) nsec;
    psCrypto_stream_chacha20(block0, sizeof block0, npub, k);
    psCrypto_onetimeauth_poly1305_init(&state, block0);
    psSodium_memzero(block0, sizeof block0);

    psCrypto_onetimeauth_poly1305_update(&state, ad, adlen);
    STORE64_LE(slen, (uint64_t) adlen);
    psCrypto_onetimeauth_poly1305_update(&state, slen, sizeof slen);

    psCrypto_stream_chacha20_xor_ic(c, m, mlen, npub, 1U, k);

    psCrypto_onetimeauth_poly1305_update(&state, c, mlen);
    STORE64_LE(slen, (uint64_t) mlen);
    psCrypto_onetimeauth_poly1305_update(&state, slen, sizeof slen);

    psCrypto_onetimeauth_poly1305_final(&state, mac);
    psSodium_memzero(&state, sizeof state);

    if (maclen_p != NULL) {
        *maclen_p = crypto_aead_chacha20poly1305_ABYTES;
    }
    return 0;
}

int
psCrypto_aead_chacha20poly1305_encrypt(unsigned char *c,
                                     unsigned long long *clen_p,
                                     const unsigned char *m,
                                     unsigned long long mlen,
                                     const unsigned char *ad,
                                     unsigned long long adlen,
                                     const unsigned char *nsec,
                                     const unsigned char *npub,
                                     const unsigned char *k)
{
    unsigned long long clen = 0ULL;
    int                ret;

    if (mlen > UINT64_MAX - crypto_aead_chacha20poly1305_ABYTES) {
        Abort(); /* LCOV_EXCL_LINE */
    }
    ret = psCrypto_aead_chacha20poly1305_encrypt_detached(c, c + mlen, NULL,
                                                          m, mlen, ad, adlen,
                                                          nsec, npub, k);
    if (clen_p != NULL) {
        if (ret == 0) {
            clen = mlen + crypto_aead_chacha20poly1305_ABYTES;
        }
        *clen_p = clen;
    }
    return ret;
}

int
psCrypto_aead_chacha20poly1305_ietf_encrypt_detached(unsigned char *c,
                                                   unsigned char *mac,
                                                   unsigned long long *maclen_p,
                                                   const unsigned char *m,
                                                   unsigned long long mlen,
                                                   const unsigned char *ad,
                                                   unsigned long long adlen,
                                                   const unsigned char *nsec,
                                                   const unsigned char *npub,
                                                   const unsigned char *k)
{
    crypto_onetimeauth_poly1305_state state;
    unsigned char                     block0[64U];
    unsigned char                     slen[8U];

    (void) nsec;
    psCrypto_stream_chacha20_ietf(block0, sizeof block0, npub, k);
    psCrypto_onetimeauth_poly1305_init(&state, block0);
    psSodium_memzero(block0, sizeof block0);

    psCrypto_onetimeauth_poly1305_update(&state, ad, adlen);
    psCrypto_onetimeauth_poly1305_update(&state, _pad0, (0x10 - adlen) & 0xf);

    psCrypto_stream_chacha20_ietf_xor_ic(c, m, mlen, npub, 1U, k);

    psCrypto_onetimeauth_poly1305_update(&state, c, mlen);
    psCrypto_onetimeauth_poly1305_update(&state, _pad0, (0x10 - mlen) & 0xf);

    STORE64_LE(slen, (uint64_t) adlen);
    psCrypto_onetimeauth_poly1305_update(&state, slen, sizeof slen);

    STORE64_LE(slen, (uint64_t) mlen);
    psCrypto_onetimeauth_poly1305_update(&state, slen, sizeof slen);

    psCrypto_onetimeauth_poly1305_final(&state, mac);
    psSodium_memzero(&state, sizeof state);

    if (maclen_p != NULL) {
        *maclen_p = crypto_aead_chacha20poly1305_ietf_ABYTES;
    }
    return 0;
}

int
psCrypto_aead_chacha20poly1305_ietf_encrypt(unsigned char *c,
                                          unsigned long long *clen_p,
                                          const unsigned char *m,
                                          unsigned long long mlen,
                                          const unsigned char *ad,
                                          unsigned long long adlen,
                                          const unsigned char *nsec,
                                          const unsigned char *npub,
                                          const unsigned char *k)
{
    unsigned long long clen = 0ULL;
    int                ret;

    if (mlen > UINT64_MAX - crypto_aead_chacha20poly1305_ietf_ABYTES) {
        Abort(); /* LCOV_EXCL_LINE */
    }
    ret = psCrypto_aead_chacha20poly1305_ietf_encrypt_detached(c, c + mlen,
                                                               NULL, m, mlen,
                                                               ad, adlen,
                                                               nsec, npub, k);
    if (clen_p != NULL) {
        if (ret == 0) {
            clen = mlen + crypto_aead_chacha20poly1305_ietf_ABYTES;
        }
        *clen_p = clen;
    }
    return ret;
}

int
psCrypto_aead_chacha20poly1305_decrypt_detached(unsigned char *m,
                                              unsigned char *nsec,
                                              const unsigned char *c,
                                              unsigned long long clen,
                                              const unsigned char *mac,
                                              const unsigned char *ad,
                                              unsigned long long adlen,
                                              const unsigned char *npub,
                                              const unsigned char *k)
{
    crypto_onetimeauth_poly1305_state state;
    unsigned char                     block0[64U];
    unsigned char                     slen[8U];
    unsigned char                     computed_mac[crypto_aead_chacha20poly1305_ABYTES];
    unsigned long long                mlen;
    int                               ret;

    (void) nsec;
    psCrypto_stream_chacha20(block0, sizeof block0, npub, k);
    psCrypto_onetimeauth_poly1305_init(&state, block0);
    psSodium_memzero(block0, sizeof block0);

    psCrypto_onetimeauth_poly1305_update(&state, ad, adlen);
    STORE64_LE(slen, (uint64_t) adlen);
    psCrypto_onetimeauth_poly1305_update(&state, slen, sizeof slen);

    mlen = clen;
    psCrypto_onetimeauth_poly1305_update(&state, c, mlen);
    STORE64_LE(slen, (uint64_t) mlen);
    psCrypto_onetimeauth_poly1305_update(&state, slen, sizeof slen);

    psCrypto_onetimeauth_poly1305_final(&state, computed_mac);
    psSodium_memzero(&state, sizeof state);

    COMPILER_ASSERT(sizeof computed_mac == 16U);
    ret = psCrypto_verify_16(computed_mac, mac);
    psSodium_memzero(computed_mac, sizeof computed_mac);
    if (m == NULL) {
        return ret;
    }
    if (ret != 0) {
        Memset(m, 0, mlen);
        return -1;
    }
    psCrypto_stream_chacha20_xor_ic(m, c, mlen, npub, 1U, k);

    return 0;
}

int
psCrypto_aead_chacha20poly1305_decrypt(unsigned char *m,
                                     unsigned long long *mlen_p,
                                     unsigned char *nsec,
                                     const unsigned char *c,
                                     unsigned long long clen,
                                     const unsigned char *ad,
                                     unsigned long long adlen,
                                     const unsigned char *npub,
                                     const unsigned char *k)
{
    unsigned long long mlen = 0ULL;
    int                ret = -1;

    if (clen >= crypto_aead_chacha20poly1305_ABYTES) {
        ret = psCrypto_aead_chacha20poly1305_decrypt_detached(m, nsec, c,
                                                              clen - crypto_aead_chacha20poly1305_ABYTES,
                                                              c + clen - crypto_aead_chacha20poly1305_ABYTES,
                                                              ad, adlen, npub,
                                                              k);
    }
    if (mlen_p != NULL) {
        if (ret == 0) {
            mlen = clen - crypto_aead_chacha20poly1305_ABYTES;
        }
        *mlen_p = mlen;
    }
    return ret;
}

int
psCrypto_aead_chacha20poly1305_ietf_decrypt_detached(unsigned char *m,
                                                   unsigned char *nsec,
                                                   const unsigned char *c,
                                                   unsigned long long clen,
                                                   const unsigned char *mac,
                                                   const unsigned char *ad,
                                                   unsigned long long adlen,
                                                   const unsigned char *npub,
                                                   const unsigned char *k)
{
    crypto_onetimeauth_poly1305_state state;
    unsigned char                     block0[64U];
    unsigned char                     slen[8U];
    unsigned char                     computed_mac[crypto_aead_chacha20poly1305_ietf_ABYTES];
    unsigned long long                mlen;
    int                               ret;

    (void) nsec;
    psCrypto_stream_chacha20_ietf(block0, sizeof block0, npub, k);
    psCrypto_onetimeauth_poly1305_init(&state, block0);
    psSodium_memzero(block0, sizeof block0);

    psCrypto_onetimeauth_poly1305_update(&state, ad, adlen);
    psCrypto_onetimeauth_poly1305_update(&state, _pad0, (0x10 - adlen) & 0xf);

    mlen = clen;
    psCrypto_onetimeauth_poly1305_update(&state, c, mlen);
    psCrypto_onetimeauth_poly1305_update(&state, _pad0, (0x10 - mlen) & 0xf);

    STORE64_LE(slen, (uint64_t) adlen);
    psCrypto_onetimeauth_poly1305_update(&state, slen, sizeof slen);

    STORE64_LE(slen, (uint64_t) mlen);
    psCrypto_onetimeauth_poly1305_update(&state, slen, sizeof slen);

    psCrypto_onetimeauth_poly1305_final(&state, computed_mac);
    psSodium_memzero(&state, sizeof state);

    COMPILER_ASSERT(sizeof computed_mac == 16U);
    ret = psCrypto_verify_16(computed_mac, mac);
    psSodium_memzero(computed_mac, sizeof computed_mac);
    if (m == NULL) {
        return ret;
    }
    if (ret != 0) {
        Memset(m, 0, mlen);
        return -1;
    }
    psCrypto_stream_chacha20_ietf_xor_ic(m, c, mlen, npub, 1U, k);

    return 0;
}

int
psCrypto_aead_chacha20poly1305_ietf_decrypt(unsigned char *m,
                                          unsigned long long *mlen_p,
                                          unsigned char *nsec,
                                          const unsigned char *c,
                                          unsigned long long clen,
                                          const unsigned char *ad,
                                          unsigned long long adlen,
                                          const unsigned char *npub,
                                          const unsigned char *k)
{
    unsigned long long mlen = 0ULL;
    int                ret = -1;

    if (clen >= crypto_aead_chacha20poly1305_ietf_ABYTES) {
        ret = psCrypto_aead_chacha20poly1305_ietf_decrypt_detached(m, nsec, c,
                                                                   clen - crypto_aead_chacha20poly1305_ietf_ABYTES,
                                                                   c + clen - crypto_aead_chacha20poly1305_ietf_ABYTES,
                                                                   ad, adlen,
                                                                   npub, k);
    }
    if (mlen_p != NULL) {
        if (ret == 0) {
            mlen = clen - crypto_aead_chacha20poly1305_ietf_ABYTES;
        }
        *mlen_p = mlen;
    }
    return ret;
}

size_t
psCrypto_aead_chacha20poly1305_ietf_keybytes(void)
{
    return crypto_aead_chacha20poly1305_ietf_KEYBYTES;
}

size_t
psCrypto_aead_chacha20poly1305_ietf_npubbytes(void)
{
    return crypto_aead_chacha20poly1305_ietf_NPUBBYTES;
}

size_t
psCrypto_aead_chacha20poly1305_ietf_nsecbytes(void)
{
    return crypto_aead_chacha20poly1305_ietf_NSECBYTES;
}

size_t
psCrypto_aead_chacha20poly1305_ietf_abytes(void)
{
    return crypto_aead_chacha20poly1305_ietf_ABYTES;
}

# ifdef USE_MATRIX_CHACHA20_POLY1305_IETF_KEYGEN
void
psCrypto_aead_chacha20poly1305_ietf_keygen(unsigned char k[crypto_aead_chacha20poly1305_ietf_KEYBYTES])
{
    randombytes_buf(k, crypto_aead_chacha20poly1305_ietf_KEYBYTES);
}
# endif /* USE_MATRIX_CHACHA20_POLY1305_IETF_KEYGEN */
#endif /* USE_MATRIX_CHACHA20_POLY1305_IETF */

#ifdef USE_MATRIX_CHACHA20_POLY1305

size_t
psCrypto_aead_chacha20poly1305_keybytes(void)
{
    return crypto_aead_chacha20poly1305_KEYBYTES;
}

size_t
psCrypto_aead_chacha20poly1305_npubbytes(void)
{
    return crypto_aead_chacha20poly1305_NPUBBYTES;
}

size_t
psCrypto_aead_chacha20poly1305_nsecbytes(void)
{
    return crypto_aead_chacha20poly1305_NSECBYTES;
}

size_t
psCrypto_aead_chacha20poly1305_abytes(void)
{
    return crypto_aead_chacha20poly1305_ABYTES;
}

# ifdef USE_MATRIX_CHACHA20_POLY1305_KEYGEN
void
psCrypto_aead_chacha20poly1305_keygen(unsigned char k[crypto_aead_chacha20poly1305_KEYBYTES])
{
    randombytes_buf(k, crypto_aead_chacha20poly1305_KEYBYTES);
}
# endif /* USE_MATRIX_CHACHA20_POLY1305_KEYGEN */
#endif /* USE_MATRIX_CHACHA20_POLY1305 */
