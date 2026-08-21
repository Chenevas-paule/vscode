#include <string.h>
#include <stdio.h>
#include "registre.h"

static struct { char nom[32]; int valeur; } compteurs[16];
static int nb_compteurs = 0;

static int trouver_compteur(const char *nom){
    for (int i = 0; i < nb_compteurs; i++) {
        if (strcmp(compteurs[i].nom, nom) == 0) {
            return i;
        }
    }

    return -1;
}

void registre_incrementer(const char *nom){
    int i = trouver_compteur(nom);
    if (i != -1){
        compteurs[i].valeur ++;
        return;
    }
    if (nb_compteurs >= 16) {
        printf("nombre de compteur max atteint\n");
        return;
    }

    
    strncpy(compteurs[nb_compteurs].nom, nom, 31);
    compteurs[nb_compteurs].valeur = 1;
    nb_compteurs++;
}

int  registre_lire(const char *nom){
    int indice = trouver_compteur(nom);

    if (indice == -1) {
        return -1;
    }
    return compteurs[indice].valeur;
}

void registre_lister(void){
    for (int i = 0; i < nb_compteurs; i++) {
        printf("%s : %d\n",compteurs[i].nom,compteurs[i].valeur);
    }
}

