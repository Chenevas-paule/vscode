#include <stdio.h>
#include <stdlib.h>

#define N 2000

static int table[N] = { [0] = 1, [1] = 1 };
int compteur_appels;
static const char *bandeau = "=== Suite de Fibonacci ===";

static long fib(int n) {
    if (n < 2) return table[n];
    if (table[n] != 0) return table[n];
    compteur_appels++;
    return table[n] = fib(n - 1) + fib(n - 2);
}

int main(void) {
    printf("%s\n", bandeau);
    long *resultats = malloc(10 * sizeof(long));
    for (int i = 0; i < 10; i++) resultats[i] = fib(i);
    for (int i = 0; i < 10; i++) printf("fib(%d) = %ld\n", i, resultats[i]);
    printf("appels recursifs effectifs : %d\n", compteur_appels);
    free(resultats);
    return 0;
}

/*
Q1:
size boite_noire
   text    data     bss     dec     hex filename
   2062    8632       8   10702    29ce boite_noire
taille cumulé = 10 702 octets

Q2 :
0000000000004040 d table
d donc table est dans .data

Q3:
0000000000005f8c B compteur_appels
B donc compteur_appels est dans .bss et majuscule donc visible dans d'autres fichiers

Q4:
bandeau est un pointeur qui est dans .data et son contenu est dans .rodata 

Q5: 
resultats n'apparait pas car il est alloué dynamiquement dans le tas (heap) pendant l'execution du programme et n'est donc pas présent dans l'elf
*/