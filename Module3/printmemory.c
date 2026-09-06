#include <stdio.h>
#include <stdint.h>

int main(void)
{
    int32_t number = 32;

    printf("The value of number is %d and its address is at %p\n", number, &number);
}