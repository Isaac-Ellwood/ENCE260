#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define FREEZING_PT 32
#define SCALE_FACTOR 5/9

int main(void){
    uint8_t n = 4;
    for (uint8_t i = 0; i <= n; i++) {
        printf("%d",i);
    }

    int32_t farenheit = 50;
    int32_t celcius = 0;

    celcius = (farenheit - FREEZING_PT) * SCALE_FACTOR;

    printf("%d degrees Farenheit is equivalent to %d degrees Celsius\n", farenheit, celcius);

    return EXIT_SUCCESS;
}

void printDigitName(uint8_t digit)
{
    switch(digit) {
        case 1:
            //
            printf("One\n");
            break;
        case 2:
            //
            printf("Two\n");
            break;
        case 3:
            //
            printf("Three\n");

            break;
        case 4:
            //
            printf("Four\n");

            break;
        case 5:
            //
            printf("Five\n");

            break;
        default:
            printf("Out of bounds\n");

            break;
    }

}