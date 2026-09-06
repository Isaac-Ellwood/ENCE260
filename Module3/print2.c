#include <stdio.h>
#include <stdint.h>

int main(void)
{
    size_t objSize;

    objSize = sizeof(float);
    printf("The object size is %zu bytes\n", objSize);
}