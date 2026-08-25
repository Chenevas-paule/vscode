#ifndef NIBBLES_H
#define NIBBLES_H
#include <stdint.h>
/* Empaquette 2 nibbles dans un octet : v1 dans les 4 bits de poids fort, v2 dans les 4 bits de poids faible.
 * Comportement indefini si v1 ou v2 > 15 (a documenter en commentaire, pas a verifier ici). */
uint8_t empaqueter_nibbles(uint8_t v1, uint8_t v2);

/* Extrait les deux nibbles d'un octet empaquete. */
void depaqueter_nibbles(uint8_t octet, uint8_t *v1, uint8_t *v2);

void empaqueter_tableau(const uint8_t valeurs[4], uint8_t sortie[2]);
void depaqueter_tableau(const uint8_t entree[2], uint8_t valeurs[4]);

#endif