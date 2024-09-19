#include "key.h"
#include "poly.h"
#include "randombytes.h"
#include <stdlib.h>
#include <string.h>

/*************************************************
 * Name:        genAx
 *
 * Description: Deterministically generate public matrix A from a seed.
 *              Entries of the A are polynomials that look uniformly random.
 *
 * Arguments:   - uint16_t *A: pointer to output matrix A
 *              - uint8_t *seed: pointer to input seed (of length
 *                                     PKSEED_BYTES)
 **************************************************/
void genAx(polyvec A[MODULE_RANK], const uint8_t seed[PKSEED_BYTES]) {  
    ALIGNED_UINT8(((PKPOLY_BYTES+SHAKE128_RATE-1)/SHAKE128_RATE)*SHAKE128_RATE) buf[4];
    __m256i f = _mm256_loadu_si256((__m256i *)seed);

#if MODULE_RANK == 2
    _mm256_store_si256(buf[0].vec, f);
    _mm256_store_si256(buf[1].vec, f);
    _mm256_store_si256(buf[2].vec, f);
    _mm256_store_si256(buf[3].vec, f);
    buf[0].coeffs[32] = 0;
    buf[0].coeffs[33] = 0;
    buf[1].coeffs[32] = 0;
    buf[1].coeffs[33] = 1;
    buf[2].coeffs[32] = 1;
    buf[2].coeffs[33] = 0;
    buf[3].coeffs[32] = 1;
    buf[3].coeffs[33] = 1;
    shake128x4(buf[0].coeffs, buf[1].coeffs, buf[2].coeffs, buf[3].coeffs, PKPOLY_BYTES, buf[0].coeffs, buf[1].coeffs, buf[2].coeffs, buf[3].coeffs, 34);
    bytes_to_Rq(&A[0].vec[0], buf[0].coeffs);
    bytes_to_Rq(&A[0].vec[1], buf[1].coeffs);
    bytes_to_Rq(&A[1].vec[0], buf[2].coeffs);
    bytes_to_Rq(&A[1].vec[1], buf[3].coeffs);




#elif MODULE_RANK == 3
    _mm256_store_si256(buf[0].vec, f);
    _mm256_store_si256(buf[1].vec, f);
    _mm256_store_si256(buf[2].vec, f);
    _mm256_store_si256(buf[3].vec, f);
    buf[0].coeffs[32] = 0;
    buf[0].coeffs[33] = 0;
    buf[1].coeffs[32] = 0;
    buf[1].coeffs[33] = 1;
    buf[2].coeffs[32] = 1;
    buf[2].coeffs[33] = 0;
    buf[3].coeffs[32] = 1;
    buf[3].coeffs[33] = 1;
    shake128x4(buf[0].coeffs, buf[1].coeffs, buf[2].coeffs, buf[3].coeffs, PKPOLY_BYTES, buf[0].coeffs, buf[1].coeffs, buf[2].coeffs, buf[3].coeffs, 34);
    bytes_to_Rq(&A[0].vec[0], buf[0].coeffs);
    bytes_to_Rq(&A[0].vec[1], buf[1].coeffs);
    bytes_to_Rq(&A[1].vec[0], buf[2].coeffs);
    bytes_to_Rq(&A[1].vec[1], buf[3].coeffs);

    _mm256_store_si256(buf[0].vec, f);
    _mm256_store_si256(buf[1].vec, f);
    _mm256_store_si256(buf[2].vec, f);
    _mm256_store_si256(buf[3].vec, f);
    buf[0].coeffs[32] = 2;
    buf[0].coeffs[33] = 0;
    buf[1].coeffs[32] = 2;
    buf[1].coeffs[33] = 1;
    buf[2].coeffs[32] = 0;
    buf[2].coeffs[33] = 2;
    buf[3].coeffs[32] = 1;
    buf[3].coeffs[33] = 2;
    shake128x4(buf[0].coeffs, buf[1].coeffs, buf[2].coeffs, buf[3].coeffs, PKPOLY_BYTES, buf[0].coeffs, buf[1].coeffs, buf[2].coeffs, buf[3].coeffs, 34);
    bytes_to_Rq(&A[2].vec[0], buf[0].coeffs);
    bytes_to_Rq(&A[2].vec[1], buf[1].coeffs);
    bytes_to_Rq(&A[0].vec[2], buf[2].coeffs);
    bytes_to_Rq(&A[1].vec[2], buf[3].coeffs);

    
    _mm256_store_si256(buf[0].vec, f);
    buf[0].coeffs[32] = 2;
    buf[0].coeffs[33] = 2;
    shake128(buf[0].coeffs, PKPOLY_BYTES, buf[0].coeffs, 34);
    bytes_to_Rq(&A[2].vec[2], buf[0].coeffs);




#elif MODULE_RANK == 4
    _mm256_store_si256(buf[0].vec, f);
    _mm256_store_si256(buf[1].vec, f);
    _mm256_store_si256(buf[2].vec, f);
    _mm256_store_si256(buf[3].vec, f);
    buf[0].coeffs[32] = 0;
    buf[0].coeffs[33] = 0;
    buf[1].coeffs[32] = 0;
    buf[1].coeffs[33] = 1;
    buf[2].coeffs[32] = 0;
    buf[2].coeffs[33] = 2;
    buf[3].coeffs[32] = 0;
    buf[3].coeffs[33] = 3;
    shake128x4(buf[0].coeffs, buf[1].coeffs, buf[2].coeffs, buf[3].coeffs, PKPOLY_BYTES, buf[0].coeffs, buf[1].coeffs, buf[2].coeffs, buf[3].coeffs, 34);
    bytes_to_Rq(&A[0].vec[0], buf[0].coeffs);
    bytes_to_Rq(&A[0].vec[1], buf[1].coeffs);
    bytes_to_Rq(&A[0].vec[2], buf[2].coeffs);
    bytes_to_Rq(&A[0].vec[3], buf[3].coeffs);

    _mm256_store_si256(buf[0].vec, f);
    _mm256_store_si256(buf[1].vec, f);
    _mm256_store_si256(buf[2].vec, f);
    _mm256_store_si256(buf[3].vec, f);
    buf[0].coeffs[32] = 1;
    buf[0].coeffs[33] = 0;
    buf[1].coeffs[32] = 1;
    buf[1].coeffs[33] = 1;
    buf[2].coeffs[32] = 1;
    buf[2].coeffs[33] = 2;
    buf[3].coeffs[32] = 1;
    buf[3].coeffs[33] = 3;
    shake128x4(buf[0].coeffs, buf[1].coeffs, buf[2].coeffs, buf[3].coeffs, PKPOLY_BYTES, buf[0].coeffs, buf[1].coeffs, buf[2].coeffs, buf[3].coeffs, 34);
    bytes_to_Rq(&A[1].vec[0], buf[0].coeffs);
    bytes_to_Rq(&A[1].vec[1], buf[1].coeffs);
    bytes_to_Rq(&A[1].vec[2], buf[2].coeffs);
    bytes_to_Rq(&A[1].vec[3], buf[3].coeffs);

    _mm256_store_si256(buf[0].vec, f);
    _mm256_store_si256(buf[1].vec, f);
    _mm256_store_si256(buf[2].vec, f);
    _mm256_store_si256(buf[3].vec, f);
    buf[0].coeffs[32] = 2;
    buf[0].coeffs[33] = 0;
    buf[1].coeffs[32] = 2;
    buf[1].coeffs[33] = 1;
    buf[2].coeffs[32] = 2;
    buf[2].coeffs[33] = 2;
    buf[3].coeffs[32] = 2;
    buf[3].coeffs[33] = 3;
    shake128x4(buf[0].coeffs, buf[1].coeffs, buf[2].coeffs, buf[3].coeffs, PKPOLY_BYTES, buf[0].coeffs, buf[1].coeffs, buf[2].coeffs, buf[3].coeffs, 34);
    bytes_to_Rq(&A[2].vec[0], buf[0].coeffs);
    bytes_to_Rq(&A[2].vec[1], buf[1].coeffs);
    bytes_to_Rq(&A[2].vec[2], buf[2].coeffs);
    bytes_to_Rq(&A[2].vec[3], buf[3].coeffs);

    _mm256_store_si256(buf[0].vec, f);
    _mm256_store_si256(buf[1].vec, f);
    _mm256_store_si256(buf[2].vec, f);
    _mm256_store_si256(buf[3].vec, f);
    buf[0].coeffs[32] = 3;
    buf[0].coeffs[33] = 0;
    buf[1].coeffs[32] = 3;
    buf[1].coeffs[33] = 1;
    buf[2].coeffs[32] = 3;
    buf[2].coeffs[33] = 2;
    buf[3].coeffs[32] = 3;
    buf[3].coeffs[33] = 3;
    shake128x4(buf[0].coeffs, buf[1].coeffs, buf[2].coeffs, buf[3].coeffs, PKPOLY_BYTES, buf[0].coeffs, buf[1].coeffs, buf[2].coeffs, buf[3].coeffs, 34);
    bytes_to_Rq(&A[3].vec[0], buf[0].coeffs);
    bytes_to_Rq(&A[3].vec[1], buf[1].coeffs);
    bytes_to_Rq(&A[3].vec[2], buf[2].coeffs);
    bytes_to_Rq(&A[3].vec[3], buf[3].coeffs);
#else
#error "This implementation works only for MODULE_RANK in {2,3,4}."
#endif
}

/*************************************************
 * Name:        genBx
 *
 * Description: Generate public vector b from a matrix A, vector s and noise e.
 *              Random noise e is generated by Gaussian sampling.
 *
 * Arguments:   - uint16_t *b: pointer to output vector b
 *              - uint16_t *A: pointer to input matrix A
 *              - uint8_t *s: pointer to input vector s
 *              - uint8_t *e_seed: pointer to input seed of error (of
 *                                     length CRYPTO_BYTES)
 **************************************************/
void genBx(polyvec *b, const polyvec A[MODULE_RANK], const polyvec *s,
           const uint8_t e_seed[CRYPTO_BYTES]) {
    // b = e
    addGaussianErrorVec(b, e_seed);

    // b = -a * s + e
    matrix_vec_mult_sub(b, A, s);
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/*************************************************
 * Name:        genSx_vec
 *
 * Description: Generate a vector of secret sparse polynomial s(x) from a seed.
 *
 * Arguments:   - secret_key *sk: pointer to output private key
 *              - const uint8_t *seed: pointer to a input seed of s(x) (of
 *                                     length CRYPTO_BYTES)
 **************************************************/
void genSx_vec(secret_key *sk, const uint8_t seed[CRYPTO_BYTES]) {
//    unsigned int i;
//    ALIGNED_UINT8(5 * SHAKE256_RATE) buf[4] = {0};
//
//#if MODULE_RANK > 4
//#error "This function assumes MODULE_RANK <= 4."
//#endif
//#if CRYPTO_BYTES != 32
//#error "This function assumes CRYPTO_BYTES == 32."
//#endif
//
//    __m256i f = _mm256_loadu_si256((__m256i*)seed);
//    _mm256_store_si256(buf[0].vec, f);
//    _mm256_store_si256(buf[1].vec, f);
//    _mm256_store_si256(buf[2].vec, f);
//    _mm256_store_si256(buf[3].vec, f);
//    buf[0].coeffs[32] = 0;
//    buf[1].coeffs[32] = MODULE_RANK * 1;
//    buf[2].coeffs[32] = MODULE_RANK * 2;
//    buf[3].coeffs[32] = MODULE_RANK * 3;
//
//    shake256x4(buf[0].coeffs, buf[1].coeffs, buf[2].coeffs, buf[3].coeffs, HWTSEEDBYTES + LWE_N/4, buf[0].coeffs, buf[1].coeffs, buf[2].coeffs, buf[3].coeffs, CRYPTO_BYTES + 1);
//
//    for (i = 0; i < MODULE_RANK; ++i) {
//        hwt(sk->vec[i].coeffs, buf[i].coeffs);
//    }
    hwt(sk, seed);
}

/*************************************************
 * Name:        genPubkey
 *
 * Description: Generate public key correspending to private key.
 *
 * Arguments:   - public_key *pk: pointer to output public key
 *              - secret_key *sk: pointer to input private key
 *              - const uint8_t *err_seed: pointer to input seed of error (of
 *                                     length CRYPTO_BYTES)
 **************************************************/
void genPubkey(public_key *pk, const secret_key *sk,
               const uint8_t err_seed[CRYPTO_BYTES]) {
    shake128(pk->seed, PKSEED_BYTES, pk->seed, PKSEED_BYTES);
    genAx(pk->A, pk->seed);

    memset(&(pk->b), 0, sizeof(uint16_t) * LWE_N);
    // Initialized at addGaussian, Unnecessary
    genBx(&(pk->b), pk->A, sk, err_seed);
}
