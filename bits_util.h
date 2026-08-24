#include <stdint.h>
#ifndef BITS_UTIL_H
#define BITS_UTIL_H

uint32_t set_bit(uint32_t x, unsigned n);      /* pose le bit n, renvoie la nouvelle valeur */
uint32_t clear_bit(uint32_t x, unsigned n);    /* efface le bit n, renvoie la nouvelle valeur */
uint32_t toggle_bit(uint32_t x, unsigned n);   /* bascule le bit n, renvoie la nouvelle valeur */
int      test_bit(uint32_t x, unsigned n);     /* renvoie 1 si le bit n est pose, 0 sinon */

#endif // BITS_UTIL_H