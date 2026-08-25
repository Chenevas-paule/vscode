#include <stdio.h>
#include <stdlib.h>
/*
1:
adresse de la variable globale initialisée à une valeur non nulle : 0x55fd77e7b028
adresse de la variable globale non initialisée : 0x55fd77e7b03c
adresse de la variable globale static initialisée à zéro : 0x55fd77e7b040
adresse de la chaîne littérale assignée à un pointeur global : 0x55fd77e79008
adresse de la variable locale dans main : 0x7ffead11a964
adresse du bloc alloué avec malloc dans main : 0x55fd9729b2a0

2:
0000000000004028 D a        dans .data
000000000000403c B b        dans .bss
0000000000004040 b c        dans .bss
0000000000004030 D str      dans .data

d et ptr sont dans la pile (stack) et ptr pointe vers un bloc alloué dans le tas (heap).

[16] .rodata PROGBITS 0000000000002000 contient les caracteres de str
[25] .data   Adresse 0x4018   Taille 0x20 contient les variables globales initialisées a et str
[26] .bss    Adresse 0x4038   Taille 0x10 contient les variables globales non initialisées b et c

*/
int a = 5;
int b;
static int c = 0;
char *str = "cartographie";
int main(void){
    int d;
    int *ptr = malloc(sizeof(int));
    printf("adresse de la variable globale initialisée à une valeur non nulle : %p\n", &a);
    printf("adresse de la variable globale non initialisée : %p\n", &b);
    printf("adresse de la variable globale static initialisée à zéro : %p\n", &c);
    printf("adresse de la chaîne littérale assignée à un pointeur global : %p\n",str);
    printf("adresse de la variable locale dans main : %p\n", &d);
    printf("adresse du bloc alloué avec malloc dans main : %p\n", ptr);

    free(ptr);
    ptr = NULL;
    return 0;
}
