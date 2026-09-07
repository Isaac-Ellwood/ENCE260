#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stddef.h>

int main(void){
    return 1;
}

void printViaPtr(int16_t* intPtr)
{
    printf("%d\n", *intPtr);
}

void print2Ints(int16_t number1, int16_t number2)
{
    printViaPtr(&number1);
    printViaPtr(&number2);
}

void swap(uint8_t* address1, uint8_t* address2)
{
    uint8_t temp = 0;
    temp = *address2;
    *address2 = *address1;
    *address1 = temp;
}