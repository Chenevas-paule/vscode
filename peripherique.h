#ifndef PERIPHERIQUE_H
#define PERIPHERIQUE_H

#include <stdint.h>

//type opaque contenant les registres du périphérique et un pointeur vers les fonctions d'accès aux registres
typedef struct peripherique peripherique_t;

//Enumération des registres 
typedef enum {
    REG_STATUS,
    REG_CONTROL,
    REG_DATA
} peripherique_registre_t;

//Registre Status
typedef union {
    uint32_t valeur;

    struct {
        uint32_t ready : 1;
        uint32_t error : 1;
        uint32_t busy  : 1;
        uint32_t       : 29;
    } bits;
} status_registre_t;

//Structure contenant les fonctions d'accès aux registres 
typedef struct {
    uint32_t (*lire)(peripherique_t *peripherique, peripherique_registre_t registre);

    void (*ecrire)(peripherique_t *peripherique, peripherique_registre_t registre, uint32_t valeur);

    void (*reset)(peripherique_t *peripherique, peripherique_registre_t registre);
} peripherique_ops_t;

//Fonctions pour créer et détruire un périphérique
peripherique_t *peripherique_creer(void);
void peripherique_detruire(peripherique_t *peripherique);

//Fonction pour obtenir les fonctions d'accès aux registres d'un périphérique
const peripherique_ops_t *peripherique_get_ops(peripherique_t *peripherique);

#endif 