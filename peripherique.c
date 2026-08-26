#include "peripherique.h"

#include <stdlib.h>

struct peripherique {
    volatile status_registre_t status;
    volatile uint8_t control;
    volatile uint8_t data;

    const peripherique_ops_t *ops;
};

static uint32_t peripherique_lire(peripherique_t *peripherique, peripherique_registre_t registre)
{
    if (peripherique == NULL) {
        return 0;
    }

    switch (registre) {
    case REG_STATUS:
        return peripherique->status.valeur;

    case REG_CONTROL:
        return peripherique->control;

    case REG_DATA:
        return peripherique->data;

    default:
        return 0;
    }
}

static void peripherique_ecrire(peripherique_t *peripherique, peripherique_registre_t registre, uint32_t valeur)
{
    if (peripherique == NULL) {
        return;
    }

    switch (registre) {
    case REG_STATUS:
        peripherique->status.valeur = valeur;
        break;

    case REG_CONTROL:
        peripherique->control = (uint8_t)valeur;
        break;

    case REG_DATA:
        peripherique->data = (uint8_t)valeur;
        break;

    default:
        break;
    }
}

static void peripherique_reset(peripherique_t *peripherique, peripherique_registre_t registre)
{
    if (peripherique == NULL) {
        return;
    }

    switch (registre) {
    case REG_STATUS:
        peripherique->status.valeur = 0;
        break;

    case REG_CONTROL:
        peripherique->control = 0;
        break;

    case REG_DATA:
        peripherique->data = 0;
        break;

    default:
        break;
    }
}

static const peripherique_ops_t peripherique_ops = {
    .lire = peripherique_lire,
    .ecrire = peripherique_ecrire,
    .reset = peripherique_reset
};

peripherique_t *peripherique_creer(void)
{
    peripherique_t *peripherique = malloc(sizeof(*peripherique));

    if (peripherique == NULL) {
        return NULL;
    }

    peripherique->status.valeur = 0;
    peripherique->control = 0;
    peripherique->data = 0;
    peripherique->ops = &peripherique_ops;

    return peripherique;
}

void peripherique_detruire(peripherique_t *peripherique)
{
    free(peripherique);
    peripherique = NULL;
}

const peripherique_ops_t *peripherique_get_ops(
    peripherique_t *peripherique)
{
    if (peripherique == NULL) {
        return NULL;
    }

    return peripherique->ops;
}