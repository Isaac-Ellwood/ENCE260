#ifndef INTN_H
#define INTN_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef NBITS
#define NBITS 24
#endif

#define NBYTES (NBITS / 8)

typedef enum {
    SUCCESS,
    OVERFLOW,
    FAIL
} IntStatus;

typedef struct {
    uint8_t data[NBYTES];
    IntStatus status;
} IntN;

void intN_readHex(IntN *number);
void intN_printHex(const IntN *number);
void intN_diagnostic(void);
int intN_isNegative(IntN number);
bool intN_isZero(IntN number);
IntStatus intN_add(IntN opa, IntN opb, IntN *result);
IntStatus intN_negate(IntN *number);
IntStatus intN_subtract(IntN opa, IntN opb, IntN *result);
IntStatus intN_read(IntN *result);
IntStatus intN_accumulator(const IntN array[], IntN *result, size_t length);
IntStatus intN_mapFunc(IntN array[], size_t length, IntStatus (*func)(IntN, IntN*));

#endif