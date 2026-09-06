#include <stdio.h>
#include <stdint.h>

int main(void)
{
    int32_t firstNumber;
    int32_t secondNumber;
    int32_t sum;
    scanf("%d %d", &firstNumber, &secondNumber);

    sum = firstNumber + secondNumber;

    printf("%d",sum);

    return 1;
}