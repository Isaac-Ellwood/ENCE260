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

IntStatus intN_negate(IntN *number)
{
    /* Two's complement: invert every bit, then add 1 */
    int carry = 1;

    for (int i = NBYTES - 1; i >= 0; i--) {
        number->data[i] = ~number->data[i] + carry;

        if (number->data[i] != 0) {
            carry = 0;
        }
    }

    return number->status;
}

IntStatus intN_subtract(IntN opa, IntN opb, IntN *result)
{
    IntN negated;

    negated = opb;
    intN_negate(&negated);

    return intN_add(opa, negated, result);
}

IntStatus intN_read(IntN *result)
{
    int c;
    int negative = 0;
    IntN temp = { {0}, SUCCESS };

    /* Skip leading whitespace */
    do {
        c = getchar();
    } while (c == ' ' || c == '\n' || c == '\t');

    /* Check for optional sign */
    if (c == '-' || c == '+') {
        if (c == '-') {
            negative = 1;
        }
        c = getchar();
    }

    /* Must have at least one digit */
    if (c < '0' || c > '9') {
        result->status = FAIL;
        return FAIL;
    }

    while (c >= '0' && c <= '9') {
        int digit = c - '0';

        /* Multiply temp by 10 */
        IntN original = temp;
        IntN times8;
        IntN times2;
        IntN multiplied;

        /* temp * 8 */
        times8 = original;
        intN_add(original, original, &times8);
        intN_add(times8, times8, &times8);
        intN_add(times8, times8, &times8);

        /* temp * 2 */
        times2 = original;
        intN_add(original, original, &times2);

        /* temp * 10 */
        intN_add(times8, times2, &multiplied);

        /* Add the new digit */
        IntN digitValue = { {0}, SUCCESS };
        digitValue.data[NBYTES - 1] = digit;

        intN_add(multiplied, digitValue, &temp);

        /*
         * If multiplication/addition overflowed, the input
         * is too large in magnitude.
         */
        if (temp.status == OVERFLOW) {
            result->status = OVERFLOW;

            /* Consume remaining digits */
            do {
                c = getchar();
            } while (c >= '0' && c <= '9');

            return OVERFLOW;
        }

        c = getchar();
    }

    if (negative) {
        intN_negate(&temp);
    }

    *result = temp;
    result->status = SUCCESS;

    return SUCCESS;
}

IntStatus intN_accumulator(const IntN array[], IntN *result, size_t length)
{
    if (length == 0) {
        // If array is empty, result is zero
        for (int i = 0; i < NBYTES; i++) {
            result->data[i] = 0;
        }
        result->status = SUCCESS;
        return SUCCESS;
    }
    
    // Initialize result to first element
    *result = array[0];
    
    // Track overflow counts
    int pos_pos_overflow = 0;  // positive + positive overflow
    int neg_neg_overflow = 0;  // negative + negative overflow
    
    // Accumulate from second element onward
    for (size_t i = 1; i < length; i++) {
        IntN temp_result;
        IntStatus add_status;
        
        // Check signs before addition
        bool opa_negative = intN_isNegative(*result);
        bool opb_negative = intN_isNegative(array[i]);
        
        // Perform addition
        add_status = intN_add(*result, array[i], &temp_result);
        
        // If addition overflowed, track the type of overflow
        if (add_status == OVERFLOW) {
            if (opa_negative && opb_negative) {
                neg_neg_overflow++;
            } else if (!opa_negative && !opb_negative) {
                pos_pos_overflow++;
            }
        }
        
        *result = temp_result;
    }
    
    // Determine final status
    // Overflow only if the number of positive+positive overflows
    // is not equal to the number of negative+negative overflows
    if (pos_pos_overflow != neg_neg_overflow) {
        result->status = OVERFLOW;
    } else {
        // Check if any individual operation overflowed but they canceled out
        // The result might still be valid if overflows cancel
        result->status = SUCCESS;
    }
    
    return result->status;
}

IntStatus intN_mapFunc(IntN array[], size_t length, IntStatus (*func)(IntN, IntN*))
{
    if (length == 0 || func == NULL) {
        return SUCCESS;
    }
    
    IntStatus maxStatus = SUCCESS;
    
    for (size_t i = 0; i < length; i++) {
        IntN result;
        IntStatus status = func(array[i], &result);
        
        // Update the array element with the result
        array[i] = result;
        
        // Track the maximum status (with OVERFLOW > FAIL > SUCCESS)
        if (status > maxStatus) {
            maxStatus = status;
        }
    }
    
    return maxStatus;
}