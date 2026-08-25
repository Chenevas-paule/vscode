#ifndef BITSTREAM_H
#define BITSTREAM_H
#include <stdint.h>
#include <stddef.h>
uint32_t extraire_bits(const uint8_t *buffer, size_t taille_buffer,size_t offset_bit, unsigned nb_bits);
void ecrire_bits(uint8_t *buffer, size_t taille_buffer,size_t offset_bit, unsigned nb_bits, uint32_t valeur);

#endif