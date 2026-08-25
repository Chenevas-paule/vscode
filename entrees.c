/*
==4200== Memcheck, a memory error detector
==4200== Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
==4200== Using Valgrind-3.24.0 and LibVEX; rerun with -h for copyright info
==4200== Command: ./entrees
==4200== 
compteur_a = 10
compteur_b = 20
==4200== Invalid free() / delete / delete[] / realloc()
==4200==    at 0x484787F: free (vg_replace_malloc.c:989)
==4200==    by 0x1091F5: detruire_entree (entrees.c:19)
==4200==    by 0x10929E: main (entrees.c:31)
==4200==  Address 0x4a56040 is 0 bytes inside a block of size 16 free'd
==4200==    at 0x484787F: free (vg_replace_malloc.c:989)
==4200==    by 0x1091F5: detruire_entree (entrees.c:19)
==4200==    by 0x109286: main (entrees.c:29)
==4200==  Block was alloc'd at
==4200==    at 0x4844818: malloc (vg_replace_malloc.c:446)
==4200==    by 0x109191: creer_entree (entrees.c:11)
==4200==    by 0x109214: main (entrees.c:23)
==4200== 
==4200== 
==4200== HEAP SUMMARY:
==4200==     in use at exit: 22 bytes in 2 blocks
==4200==   total heap usage: 5 allocs, 4 frees, 1,078 bytes allocated
==4200== 
==4200== 11 bytes in 1 blocks are definitely lost in loss record 1 of 2
==4200==    at 0x4844818: malloc (vg_replace_malloc.c:446)
==4200==    by 0x1091AD: creer_entree (entrees.c:12)
==4200==    by 0x109214: main (entrees.c:23)
==4200== 
==4200== 11 bytes in 1 blocks are definitely lost in loss record 2 of 2
==4200==    at 0x4844818: malloc (vg_replace_malloc.c:446)
==4200==    by 0x1091AD: creer_entree (entrees.c:12)
==4200==    by 0x10922C: main (entrees.c:24)
==4200== 
==4200== LEAK SUMMARY:
==4200==    definitely lost: 22 bytes in 2 blocks
==4200==    indirectly lost: 0 bytes in 0 blocks
==4200==      possibly lost: 0 bytes in 0 blocks
==4200==    still reachable: 0 bytes in 0 blocks
==4200==         suppressed: 0 bytes in 0 blocks
==4200== 
==4200== For lists of detected and suppressed errors, rerun with: -s
==4200== ERROR SUMMARY: 3 errors from 3 contexts (suppressed: 0 from 0)

il detecte 3 erreurs : 
1) double free sur le meme pointeur (detruire_entree(a))
2 et 3) on pert la reference sur le bloc alloué pour le nom de l'entree (detruire_entree(a) et detruire_entree(b))

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *nom;
    int   valeur;
} entree_t;

entree_t *creer_entree(const char *nom, int valeur) {
    entree_t *e = malloc(sizeof(entree_t));
    e->nom = malloc(strlen(nom) + 1);
    strcpy(e->nom, nom);
    e->valeur = valeur;
    return e;
}

void detruire_entree(entree_t *e) {
    free(e->nom);  
    free(e); 
}

int main(void) {
    entree_t *a = creer_entree("compteur_a", 10);
    entree_t *b = creer_entree("compteur_b", 20);

    printf("%s = %d\n", a->nom, a->valeur);
    printf("%s = %d\n", b->nom, b->valeur);

    detruire_entree(a);
    detruire_entree(b);

    return 0;
}
/*
apres correction :
==4776== All heap blocks were freed -- no leaks are possible
==4776== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0) 
*/