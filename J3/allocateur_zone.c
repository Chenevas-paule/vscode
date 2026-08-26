#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#define TAILLE_ZONE 4096

static uint8_t zone_memoire[TAILLE_ZONE];
static size_t  curseur = 0;

/* Retourne un pointeur vers un bloc de "taille" octets dans zone_memoire, ou NULL
 * si la zone est epuisee. Ne fournit PAS de liberation individuelle (allocateur
 * "bump" -- le plus simple possible, uniquement pedagogique). */
void *zone_alloc(size_t taille){
    if (curseur + taille > TAILLE_ZONE) {
        return NULL; 
    }
    void *ptr = &zone_memoire[curseur];
    curseur += taille;
    return ptr;
}

/* Remet le curseur a zero : "libere" tout d'un coup (pas de granularite plus fine). */
void zone_reset(void){
    curseur = 0;
}

int main(void){
    void *p1 = zone_alloc(100);
    void *p2 = zone_alloc(200);
    void *p3 = zone_alloc(300);

    printf("p1: %p\n", p1);
    printf("p2: %p\n", p2);
    printf("p3: %p\n", p3);

    void *p4 = zone_alloc(4000); 
    printf("p4: %p\n", p4);

    zone_reset();

    void *p5 = zone_alloc(150); 
    printf("p5: %p\n", p5);
    return 0;
}
/*
resultat :
p1: 0x5637eb71c040
p2: 0x5637eb71c0a4
p3: 0x5637eb71c16c
p4: (nil)
p5: 0x5637eb71c040
tout est correct

on n'a pas besoin de malloc et free car on alloue dans une zone de memoire statique prédefinie au debut du programme (tableau de uint_8t : zone_memoire)
la limite est qu'on ne peut pas liberer un bloc individuel, on ne peut que tout liberer d'un coup avec zone_reset()
*/