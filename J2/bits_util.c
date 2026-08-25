#include <stdio.h>
#include <stdint.h>
#include "bits_util.h"

uint32_t set_bit(uint32_t x, unsigned n)      /* pose le bit n, renvoie la nouvelle valeur */
{
    if (n >= 32) {
        fprintf(stderr, "Erreur : l'indice doit être compris entre 0 et 31.\n");
        return x;
    }
    return x | (1 << n);
}

uint32_t clear_bit(uint32_t x, unsigned n)    /* efface le bit n, renvoie la nouvelle valeur */
{
    if (n >= 32) {
        fprintf(stderr, "Erreur : l'indice doit être compris entre 0 et 31.\n");
        return x;
    }
    return x & ~(1 << n);
}

uint32_t toggle_bit(uint32_t x, unsigned n)   /* bascule le bit n, renvoie la nouvelle valeur */
{
    if (n >= 32) {
        fprintf(stderr, "Erreur : l'indice doit être compris entre 0 et 31.\n");
        return x;
    }
    return x ^ (1 << n);
}

int      test_bit(uint32_t x, unsigned n)     /* renvoie 1 si le bit n est pose, 0 sinon */
{
    if (n >= 32) {
        fprintf(stderr, "Erreur : l'indice doit être compris entre 0 et 31.\n");
        return x;
    }
    return (x >> n) & 1;
}