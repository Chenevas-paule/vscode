#include "bitstream.h"
uint32_t extraire_bits(const uint8_t *buffer, size_t taille_buffer,size_t offset_bit, unsigned nb_bits){
    assert((nb_bits <= 32) && (offset_bit + nb_bits <= taille_buffer * 8)); 

    size_t octet_index = offset_bit / 8;
    size_t bit_index = offset_bit % 8;

    uint32_t result = 0;
    for(int i = 0; i<nb_bits;i++){
        result |= ((buffer[octet_index] >> bit_index) & 1) << i;
        bit_index++;
        if(bit_index == 8){
            bit_index = 0; 
            octet_index++;
        }
    }

    void ecrire_bits(uint8_t *buffer, size_t taille_buffer,size_t offset_bit, unsigned nb_bits, uint32_t valeur){
        
    }

    return result;
}