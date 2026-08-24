#include <stdio.h>
#include <stdint.h>
//exo 1
#include <assert.h>
#include "bits_util.h"
//exo 2
#include "config_masques.h"
#include "config_bitfield.h"
//exo 3
#include "nibbles.h"
//exo 4
#include "ieee754.h"

/*
-------------------------------------------------------------------------------------------------------
    EXO 1
*/
void exo1(void){
    uint32_t x = 0;
    x = set_bit(x, 3);
    assert(test_bit(x, 3) == 1);
    x = clear_bit(x, 3);
    assert(test_bit(x, 3) == 0);
    x = toggle_bit(x, 7);
    assert(test_bit(x, 7) == 1);
    printf("tous les tests passent\n");
}

/*
-------------------------------------------------------------------------------------------------------
    EXO 2
*/
/*
les champs de bits sont pratiques pour un usage *interne à un seul programme, compilé par un seul compilateur, sur une seule plateforme*
les masques manuels sont pratiques quand un format binaire doit être **portable**
*/
void exo2(void){
    uint8_t rm = config_m_construire(1, 2, 5);
    struct config_bf r_cfg = config_bf_init(1, 2, 5);
    printf("size rm = %zu\n", sizeof(rm));
    printf("size r_cfg = %zu\n", sizeof(r_cfg));
}

/*
-------------------------------------------------------------------------------------------------------
    EXO 3
*/
int exo3(void){
    const uint8_t valeurs[4] = {3, 12, 7, 15};
    uint8_t octets[2];
    uint8_t valeurs_depaquetees[4];

    empaqueter_tableau(valeurs, octets);

    printf("Octets empaquetes : ");
    for (size_t i = 0; i < 2; i++) {
        printf("%02X ", octets[i]);
    }
    printf("\n");

    depaqueter_tableau(octets, valeurs_depaquetees);

    for (size_t i = 0; i < 4; i++) {
        if(valeurs_depaquetees[i] != valeurs[i]){
            printf("Erreur : valeur depaquetee %u ne correspond pas a la valeur originale %u\n", valeurs_depaquetees[i], valeurs[i]);
            return 1;
        }
    }
    printf("Les 4 valeurs de depart sont retrouvees.\n");
    return 0;
}


/*
-------------------------------------------------------------------------------------------------------
    EXO 4
*/
void exo4(void){
    float f = 1.0f;
    afficher_ieee754(f);
    f = -1.0f;
    afficher_ieee754(f);
    f = 0.5f;
    afficher_ieee754(f);
    f = 3.14f;
    afficher_ieee754(f);
}

/*
-------------------------------------------------------------------------------------------------------
    EXO 5
*/


/*
-------------------------------------------------------------------------------------------------------
    EXO 6
*/


int main(void)
{
    exo4();
    return 0;
}
