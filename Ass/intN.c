#include "intN.h"

void intN_readHex(IntN *number)
{
    for (int i = 0; i < NBYTES; i++) {
        scanf("%2hhx", &number->data[i]);
    }

    number->status = SUCCESS;
}

void intN_printHex(const IntN *number)
{
    printf("0x");

    for (int i = 0; i < NBYTES; i++) {
        printf("%02hhx", number->data[i]);
    }
}

void intN_diagnostic(void)
{
    printf("Diagnostic: NBITS=%d, NBYTES=%d\n\n", NBITS, NBYTES);
}

int intN_isNegative(IntN number)
{
    return (number.data[0] & 0x80) != 0;
}

bool intN_isZero(IntN number)
{
    for (int i = 0; i < NBYTES; i++) {
        if (number.data[i] != 0) {
            return false;
        }
    }

    return true;
}

IntStatus intN_add(IntN opa, IntN opb, IntN *result)
{
    int carry = 0;

    for (int i = NBYTES - 1; i >= 0; i--) {
        int sum = opa.data[i] + opb.data[i] + carry;

        result->data[i] = sum & 0xFF;
        carry = sum >> 8;
    }

    bool opaNegative = intN_isNegative(opa);
    bool opbNegative = intN_isNegative(opb);
    bool resultNegative = intN_isNegative(*result);

    if ((!opaNegative && !opbNegative && resultNegative) || (opaNegative && opbNegative && !resultNegative)) {
        result->status = OVERFLOW;
    } else {
        result->status = opa.status > opb.status ? opa.status : opb.status;
    }

    return result->status;

    
}