#include "endianness.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>


uint32_t swap32(uint32_t x)
{
    return ((x & 0x000000FFu) << 24) | ((x & 0x0000FF00u) << 8) | ((x & 0x00FF0000u) >> 8) | ((x & 0xFF000000u) >> 24);
}

uint16_t swap16(uint16_t x)
{
    return ((x & 0x00FFu) << 8) | ((x & 0xFF00u) >> 8);
}
/* Inverse en place l'ordre des octets de chaque element du tableau (16 bits). */
void inverser_endianness16(uint16_t tab[], size_t n){
    for (size_t i = 0; i < n; i++) {
        tab[i] = swap16(tab[i]);
    }
}

/* Meme principe pour un tableau de valeurs 32 bits. */
void inverser_endianness32(uint32_t tab[], size_t n){
    for (size_t i = 0; i < n; i++) {
        tab[i] = swap32(tab[i]);
    }
}

int est_little_endian(void)
{
    union {
        uint16_t valeur;
        uint8_t octets[2];
    } u;

    u.valeur = 1;

    return u.octets[0] == 1;
}

