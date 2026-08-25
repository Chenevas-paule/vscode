#include "ieee754.h"
#include <stdio.h>
#include <stdint.h>
#include "bits_util.h"

void afficher_ieee754(float f){
    union {
        float f;
        uint32_t u;
    } float_union;
    float_union.f = f;
    for (int i = 31; i >= 0; i--) {
        printf("%u", test_bit(float_union.u, i));
    }
    printf("\n");
    printf("bit de signe : %u\n", (float_union.u >> 31) & 1);
    printf("bits d'exposant : %u\n", (float_union.u >> 23) & 0xFF);
    printf("bits de mantisse : %u\n", float_union.u & 0x7FFFFF);
}