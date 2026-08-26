#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "peripherique.h"

//variable globale pour indiquer si le programme doit continuer ou non
int continuer;

//definition des commandes et de leurs handlers
typedef void (*commande_handler_t)(peripherique_t *peripherique, const peripherique_ops_t *ops, int arg_cnt, char **argv);

//structure pour stocker le nom de la commande et son handler
typedef struct {
    const char *nom;
    commande_handler_t handler;
} commande_t;

static const commande_t commandes[] = {
    { "READ",  handle_read  },
    { "WRITE", handle_write },
    { "RESET", handle_reset },
    { "DUMP",  handle_dump  },
    { "QUIT",  handle_quit  }
};

#define NB_COMMANDES (sizeof(commandes) / sizeof(commandes[0]))

//fonction pour trouver le registre demandé par l'utilisateur
static int trouver_registre(const char *nom, peripherique_registre_t *registre)
{
    if (strcmp(nom, "STATUS") == 0) {
        *registre = REG_STATUS;
        return 1;
    }

    if (strcmp(nom, "CONTROL") == 0) {
        *registre = REG_CONTROL;
        return 1;
    }

    if (strcmp(nom, "DATA") == 0) {
        *registre = REG_DATA;
        return 1;
    }

    return 0;
}

//fonction handle commande READ
static void handle_read(peripherique_t *peripherique, const peripherique_ops_t *ops, int arg_cnt, char **argv)
{
    peripherique_registre_t registre;

    if (arg_cnt != 2) {
        printf("Usage : READ <registre>\n");
        return;
    }

    if (!trouver_registre(argv[1], &registre)) {
        printf("Erreur : registre inconnu '%s'\n", argv[1]);
        return;
    }

    uint32_t valeur = ops->lire(peripherique, registre);

    printf("%s = 0x%08X\n", argv[1], valeur);
}

//fonction handle commande WRITE
static void handle_write(peripherique_t *peripherique, const peripherique_ops_t *ops, int arg_cnt, char **argv)
{
    peripherique_registre_t registre;
    char *fin;
    unsigned long valeur;

    if (arg_cnt != 3) {
        printf("Usage : WRITE <registre> <valeur>\n");
        return;
    }

    if (!trouver_registre(argv[1], &registre)) {
        printf("Erreur : registre inconnu '%s'\n", argv[1]);
        return;
    }

    valeur = strtoul(argv[2], &fin, 0);

    if (*argv[2] == '\0' || *fin != '\0') {
        printf("Erreur : valeur invalide '%s'\n", argv[2]);
        return;
    }

    if (valeur > UINT32_MAX) {
        printf("Erreur : valeur trop grande\n");
        return;
    }

    ops->ecrire(peripherique, registre, (uint32_t)valeur);

    printf("%s <- 0x%08lX\n", argv[1], valeur);
}

//fonction handle commande RESET
static void handle_reset(peripherique_t *peripherique, const peripherique_ops_t *ops, int arg_cnt, char **argv)
{
    peripherique_registre_t registre;

    if (arg_cnt != 2) {
        printf("Usage : RESET <registre>\n");
        return;
    }

    if (!trouver_registre(argv[1], &registre)) {
        printf("Erreur : registre inconnu '%s'\n", argv[1]);
        return;
    }

    ops->reset(peripherique, registre);

    printf("%s reset\n", argv[1]);
}

//fonction handle commande DUMP
static void handle_dump(peripherique_t *peripherique, const peripherique_ops_t *ops, int arg_cnt, char **argv)
{
    (void)argv;

    if (arg_cnt != 1) {
        printf("Usage : DUMP\n");
        return;
    }

    printf("STATUS  = 0x%08X\n",
           ops->lire(peripherique, REG_STATUS));

    printf("CONTROL = 0x%02X\n",
           (uint8_t)ops->lire(peripherique, REG_CONTROL));

    printf("DATA    = 0x%02X\n",
           (uint8_t)ops->lire(peripherique, REG_DATA));
}

//fonction handle commande QUIT
static void handle_quit(peripherique_t *peripherique, const peripherique_ops_t *ops, int arg_cnt, char **argv)
{
    (void)argv;

    if (arg_cnt != 1) {
        printf("Usage : QUIT\n");
        return;
    }

    continuer = 0;
}

//fonction pour trouver la commande correspondant au nom donné
static const commande_t *trouver_commande(const char *nom)
{
    for (size_t i = 0; i < NB_COMMANDES; ++i) {
        if (strcmp(nom, commandes[i].nom) == 0) {
            return &commandes[i];
        }
    }

    return NULL;
}

#define MAX_ARGUMENTS 4


//fonction pour découper une ligne en arguments
static int decouper_ligne(char *ligne, char **argv)
{
    int arg_cnt = 0;
    char *token = strtok(ligne, " \t\r\n");

    while (token != NULL && arg_cnt < MAX_ARGUMENTS) {
        argv[arg_cnt++] = token;
        token = strtok(NULL, " \t\r\n");
    }

    return arg_cnt;
}

/*
Question 4  :
Les tables "peripherique_ops_t" et "commandes" sont placées dans la section .rodata car elles contient des données constantes (static const).
Par contre peripherique_t est alloué dynamiquement avec malloc donc il est placé dans le tas (heap)
L'indicateur volatile ne change pas la zone memoire utilisé mais le comportement du compilateur pour l'acces a ces variables.


 Compte-rendu :
 La table de callbacks permet de regrouper les opérations lire, écrire et reset.
 Elle évite d'avoir une fonction différente pour chaque registre et évite un switch.
 L'opacité de peripherique_t empêche les accès directs aux registres depuis main.c.
 Elle améliore donc l'encapsulation et oblige à utiliser l'interface du périphérique.
 DUMP est intégré à la même table que les autres commandes.
 Tous les gestionnaires ont la même signature, et DUMP vérifie simplement ses arguments.

*/
int main(void)
{
    peripherique_t *peripherique = peripherique_creer();

    if (peripherique == NULL) {
        fprintf(stderr,"Erreur : impossible de creer le peripherique\n");
        return EXIT_FAILURE;
    }

    const peripherique_ops_t *ops = peripherique_get_ops(peripherique);

    continuer = 1;

    char ligne[256];

    while (continuer && fgets(ligne, sizeof(ligne), stdin)) {
        char *argv[MAX_ARGUMENTS];

        int arg_cnt = decouper_ligne(ligne, argv);

        if (arg_cnt == 0) {
            continue;
        }

        const commande_t *commande = trouver_commande(argv[0]);

        if (commande == NULL) {
            printf("Erreur : commande inconnue '%s'\n", argv[0]);
            continue;
        }

        commande->handler(peripherique, ops, arg_cnt, argv);
    }

    peripherique_detruire(peripherique);

    return EXIT_SUCCESS;
}