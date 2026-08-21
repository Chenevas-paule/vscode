#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <signal.h>
#include <unistd.h>
//pour l'exo 5 
#include "registre.h"
//pour l'exo 6
#include "tableaux_util.h"
/*
-------------------------------------------------------------------------------------------------------
    EXO 1
*/
void exo1(void){
    printf("%-10s %-12s %-22s %-22s\n","Type", "Taille (o)", "Min", "Max");
    printf("%-10s %-12s %-22s %-22s\n","----", "----------", "---", "---");

    printf("%-10s %-12zu %-22d %-22d\n","int8_t", sizeof(int8_t), INT8_MIN, INT8_MAX);

    printf("%-10s %-12zu %-22u %-22u\n","uint8_t", sizeof(uint8_t), 0u, UINT8_MAX);

    printf("%-10s %-12zu %-22d %-22d\n","int16_t", sizeof(int16_t), INT16_MIN, INT16_MAX);

    printf("%-10s %-12zu %-22u %-22u\n","uint16_t", sizeof(uint16_t), 0u, UINT16_MAX);

    printf("%-10s %-12zu %-22d %-22d\n","int32_t", sizeof(int32_t), INT32_MIN, INT32_MAX);

    printf("%-10s %-12zu %-22u %-22u\n","uint32_t", sizeof(uint32_t), 0u, UINT32_MAX);

    printf("%-10s %-12zu %-22" PRId64 " %-22" PRId64 "\n","int64_t", sizeof(int64_t), INT64_MIN, INT64_MAX);

    printf("%-10s %-12zu %-22" PRIu64 " %-22" PRIu64 "\n","uint64_t", sizeof(uint64_t), UINT64_C(0), UINT64_MAX);
}

/*
-------------------------------------------------------------------------------------------------------
    EXO 2
*/
int addition_sure(int32_t a, int32_t b, int32_t *resultat){

    if (a > 0 && b > 0 && a > INT32_MAX - b)
        return -1;

    if (a < 0 && b < 0 && a < INT32_MIN - b)
        return -1;

    *resultat = a + b;
    return 0;
}

int multiplication_sure(int32_t a, int32_t b, int32_t *resultat)
{
    int64_t produit = (int64_t)a * (int64_t)b;

    if (produit > INT32_MAX || produit < INT32_MIN)
        return -1;

    *resultat = (int32_t)produit;
    return 0;
}

void exo2(void){
struct cas_test { int32_t a, b; int deborde_addition; int deborde_multiplication; };
struct cas_test tests[] = {
    { 100, 200, 0, 0 },
    { INT32_MAX, 1, 1, 0 },
    { INT32_MIN, -1, 1, 1 },
    { 100000, 100000, 0, 1 },
    { 3, 4, 0, 0 },
};

 int nb_tests = 5;

    for (int i = 0; i < nb_tests; i++) {
        int32_t resultat;

        int erreur_addition = addition_sure(tests[i].a, tests[i].b, &resultat);

        printf("Test %d : a = %" PRId32 ", b = %" PRId32 "\n",i + 1, tests[i].a, tests[i].b);

        if (erreur_addition == -1) {
            printf("  Addition : ECHEC\n");
        } else {
            printf("  Addition : Ok\n");
        }

        int erreur_multiplication = multiplication_sure(tests[i].a, tests[i].b, &resultat);

        if (erreur_multiplication == -1) {
            printf("  Multiplication : ECHEC\n");
        } else {
            printf("  Multiplication : OK\n");
        }

        printf("\n");
    }
}

/*
-------------------------------------------------------------------------------------------------------
    EXO 3
*/
struct config {
    const char *nom_application;
    const char *version;
    int         max_connexions;
    int         mode_debug;   // 0 ou 1
};

static const struct config CONFIG_PAR_DEFAUT = { 
    .nom_application = "default_App",
    .version = "1.0",
    .max_connexions = 100,
    .mode_debug = 0
 };

const char *config_nom(const struct config *cfg){
    return cfg->nom_application;
}
const char *config_version(const struct config *cfg){
    return cfg->version;
}
int config_max_connexions(const struct config *cfg){
    return cfg->max_connexions;
}
int config_mode_debug(const struct config *cfg){
    return cfg->mode_debug;

}
void config_afficher(const struct config *cfg){
    printf("Application    : %s\n", config_nom(cfg));
    printf("Version        : %s\n", config_version(cfg));
    printf("Max connexions : %d\n", config_max_connexions(cfg));
    printf("Mode debug     : %d\n", config_mode_debug(cfg));
}

void exo3(void){
    config_afficher(&CONFIG_PAR_DEFAUT);
}

/*
-------------------------------------------------------------------------------------------------------
    EXO 4
*/

static volatile sig_atomic_t arret = 0;

static void gestionnaire_sigint(int signum) {
    (void)signum;
    arret = 1;
}

int exo4(void){
    signal(SIGINT, gestionnaire_sigint);
    int temps = 0;

    while(arret == 0){
        sleep(1);
        temps++;
        printf("Temps ecoule : %ds\n",temps);
    }
    printf("Chronometre arrete apres: %ds\n",temps);
    return 0;
}

/*
-------------------------------------------------------------------------------------------------------
    EXO 5
*/
void exo5(void){
    registre_incrementer("requetes");
    registre_incrementer("erreurs");
    registre_incrementer("requetes");
    registre_incrementer("requetes");
    registre_lister();
    printf("erreurs = %d\n", registre_lire("erreurs"));
    printf("inconnu = %d\n", registre_lire("inconnu"));
}

/*
-------------------------------------------------------------------------------------------------------
    EXO 6
*/
void exo6(void){
    int tab1[] = {8, 3, 14, 1, 9, 6, 12, 5};
    int tab2[8];
    copier_tableau(tab2, tab1, 8);
    afficher_tableau("tab1", tab1, 8);
    afficher_tableau("tab2", tab2, 8);
    printf("Apres copie : tableaux %s\n",
           comparer_tableaux(tab1, tab2, 8) ? "identiques" : "differents");

    tab2[3] = 42;
    printf("Apres modification : tableaux %s\n",
           comparer_tableaux(tab1, tab2, 8) ? "identiques" : "differents");
}

int main(void)
{
    exo6();
    return 0;
}
