#ifndef ENDIANNESS_H
#define ENDIANNESS_H
#include <stdint.h>
#include <stddef.h>
uint32_t swap32(uint32_t x);
uint16_t swap16(uint16_t x);
/* Inverse en place l'ordre des octets de chaque element du tableau (16 bits). */
void inverser_endianness16(uint16_t tab[], size_t n);

/* Meme principe pour un tableau de valeurs 32 bits. */
void inverser_endianness32(uint32_t tab[], size_t n);

int est_little_endian(void);
#endif