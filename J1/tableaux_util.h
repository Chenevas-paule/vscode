#ifndef TABLEAUX_UTIL_H
#define TABLEAUX_UTIL_H
#include <stdint.h>

void copier_tableau(int *restrict dst, const int *restrict src, size_t n);
int  comparer_tableaux(const int *a, const int *b, size_t n);   // 1 si identiques, 0 sinon
void afficher_tableau(const char *etiquette, const int *tab, size_t n);

#endif // TABLEAUX_UTIL_H