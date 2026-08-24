#include "nibbles.h"
/* Empaquette 2 nibbles dans un octet : v1 dans les 4 bits de poids fort, v2 dans les 4 bits de poids faible.
 * Comportement indefini si v1 ou v2 > 15 (a documenter en commentaire, pas a verifier ici). */
uint8_t empaqueter_nibbles(uint8_t v1, uint8_t v2){
    return (v1 << 4) | v2;
}

/* Extrait les deux nibbles d'un octet empaquete. */
void depaqueter_nibbles(uint8_t octet, uint8_t *v1, uint8_t *v2){
    *v1 = (octet >> 4) & 0x0F;
    *v2 = octet & 0x0F;
}

void empaqueter_tableau(const uint8_t valeurs[4], uint8_t sortie[2]){
    sortie[0] = empaqueter_nibbles(valeurs[0], valeurs[1]);
    sortie[1] = empaqueter_nibbles(valeurs[2], valeurs[3]);
}
void depaqueter_tableau(const uint8_t entree[2], uint8_t valeurs[4]){
    depaqueter_nibbles(entree[0], &valeurs[0], &valeurs[1]);
    depaqueter_nibbles(entree[1], &valeurs[2], &valeurs[3]);
}