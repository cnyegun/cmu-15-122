#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

int main(void) {
    printf("=== Fundamental integer types ===\n");
    printf("char:               %zu\n", sizeof(char));
    printf("signed char:        %zu\n", sizeof(signed char));
    printf("unsigned char:      %zu\n", sizeof(unsigned char));
    printf("short:              %zu\n", sizeof(short));
    printf("unsigned short:     %zu\n", sizeof(unsigned short));
    printf("int:                %zu\n", sizeof(int));
    printf("unsigned int:       %zu\n", sizeof(unsigned int));
    printf("long:               %zu\n", sizeof(long));
    printf("unsigned long:      %zu\n", sizeof(unsigned long));
    printf("long long:          %zu\n", sizeof(long long));
    printf("unsigned long long: %zu\n", sizeof(unsigned long long));

    printf("\n=== Floating point types ===\n");
    printf("float:              %zu\n", sizeof(float));
    printf("double:             %zu\n", sizeof(double));
    printf("long double:        %zu\n", sizeof(long double));

    printf("\n=== Boolean and size types ===\n");
    printf("_Bool:              %zu\n", sizeof(_Bool));
    printf("size_t:             %zu\n", sizeof(size_t));
    printf("ptrdiff_t:          %zu\n", sizeof(ptrdiff_t));

    printf("\n=== Pointer types ===\n");
    printf("void*:              %zu\n", sizeof(void *));
    printf("char*:              %zu\n", sizeof(char *));
    printf("int*:               %zu\n", sizeof(int *));
    printf("double*:            %zu\n", sizeof(double *));

    printf("\n=== Fixed-width integer types (stdint.h) ===\n");
    printf("int8_t:             %zu\n", sizeof(int8_t));
    printf("uint8_t:            %zu\n", sizeof(uint8_t));
    printf("int16_t:            %zu\n", sizeof(int16_t));
    printf("uint16_t:           %zu\n", sizeof(uint16_t));
    printf("int32_t:            %zu\n", sizeof(int32_t));
    printf("uint32_t:           %zu\n", sizeof(uint32_t));
    printf("int64_t:            %zu\n", sizeof(int64_t));
    printf("uint64_t:           %zu\n", sizeof(uint64_t));
    printf("intptr_t:           %zu\n", sizeof(intptr_t));
    printf("uintptr_t:          %zu\n", sizeof(uintptr_t));

    return 0;
}

