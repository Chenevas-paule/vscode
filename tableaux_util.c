#include <stdio.h>
#include <stdint.h>
#include "tableaux_util.h"

void copier_tableau(int *restrict dst, const int *restrict src, size_t n){
    for (size_t i = 0; i < n; i++) {
        dst[i] = src[i];
    }
}
int  comparer_tableaux(const int *a, const int *b, size_t n){   // 1 si identiques, 0 sinon
    for (size_t i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}
void afficher_tableau(const char *etiquette, const int *tab, size_t n){
    printf("%s: ", etiquette);
    for (size_t i = 0; i < n; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
}