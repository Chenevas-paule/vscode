#ifndef REGISTRE_H
#define  REGISTRE_H

void registre_incrementer(const char *nom);   // cree le compteur "nom" s'il n'existe pas encore, puis l'incremente
int  registre_lire(const char *nom);           // renvoie la valeur du compteur "nom", ou -1 s'il n'existe pas
void registre_lister(void);                    // affiche tous les compteurs connus et leur valeur

#endif