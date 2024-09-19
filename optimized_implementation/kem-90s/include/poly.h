#ifndef SMAUG_POLY_H
#define SMAUG_POLY_H

#include "align.h"
#include "parameters.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef ALIGNED_INT16(LWE_N) poly;

typedef struct {
    poly vec[MODULE_RANK];
} polyvec;

#define vec_vec_mult_add SMAUG_NAMESPACE(vec_vec_mult_add)
void vec_vec_mult_add(poly *r, const polyvec *a, const polyvec *b,
                      const uint8_t mod);
#define matrix_vec_mult_add SMAUG_NAMESPACE(matrix_vec_mult_add)
void matrix_vec_mult_add(polyvec *r, const polyvec a[MODULE_RANK],
                         const polyvec *b);
#define matrix_vec_mult_sub SMAUG_NAMESPACE(matrix_vec_mult_sub)
void matrix_vec_mult_sub(polyvec *r, const polyvec a[MODULE_RANK],
                         const polyvec *b);

#endif // SMAUG_POLY_H
