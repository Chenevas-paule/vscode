#include <stdio.h>

int compteur_global = 5;
static int compteur_prive = 10;

static void fonction_privee(void) {
    printf("privee\n");
}

void fonction_publique(void) {
    fonction_privee();
}

int main(void) {
    fonction_publique();
    printf("%d %d\n", compteur_global, compteur_prive);
    return 0;
}
