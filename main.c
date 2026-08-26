#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "peripherique.h"

typedef struct {
    peripherique_t *peripherique;
    const peripherique_ops_t *ops;
    int continuer;
} contexte_t;

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

static void handle_read(contexte_t *ctx, int argc, char **argv)
{
    peripherique_registre_t registre;

    if (argc != 2) {
        printf("Usage : READ <registre>\n");
        return;
    }

    if (!trouver_registre(argv[1], &registre)) {
        printf("Erreur : registre inconnu '%s'\n", argv[1]);
        return;
    }

    uint32_t valeur = ctx->ops->lire(ctx->peripherique, registre);

    printf("%s = 0x%08X\n", argv[1], valeur);
}

static void handle_write(contexte_t *ctx, int argc, char **argv)
{
    peripherique_registre_t registre;
    char *fin;
    unsigned long valeur;

    if (argc != 3) {
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

    ctx->ops->ecrire(ctx->peripherique,
                     registre,
                     (uint32_t)valeur);

    printf("%s <- 0x%08lX\n", argv[1], valeur);
}

static void handle_reset(contexte_t *ctx, int argc, char **argv)
{
    peripherique_registre_t registre;

    if (argc != 2) {
        printf("Usage : RESET <registre>\n");
        return;
    }

    if (!trouver_registre(argv[1], &registre)) {
        printf("Erreur : registre inconnu '%s'\n", argv[1]);
        return;
    }

    ctx->ops->reset(ctx->peripherique, registre);

    printf("%s reset\n", argv[1]);
}

static void handle_dump(contexte_t *ctx, int argc, char **argv)
{
    (void)argv;

    if (argc != 1) {
        printf("Usage : DUMP\n");
        return;
    }

    printf("STATUS  = 0x%08X\n",
           ctx->ops->lire(ctx->peripherique, REG_STATUS));

    printf("CONTROL = 0x%02X\n",
           (uint8_t)ctx->ops->lire(ctx->peripherique, REG_CONTROL));

    printf("DATA    = 0x%02X\n",
           (uint8_t)ctx->ops->lire(ctx->peripherique, REG_DATA));
}

static void handle_quit(contexte_t *ctx, int argc, char **argv)
{
    (void)argv;

    if (argc != 1) {
        printf("Usage : QUIT\n");
        return;
    }

    ctx->continuer = 0;
}

typedef void (*commande_handler_t)(contexte_t *ctx, int argc, char **argv);

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

static int decouper_ligne(char *ligne, char **argv)
{
    int argc = 0;
    char *token = strtok(ligne, " \t\r\n");

    while (token != NULL && argc < MAX_ARGUMENTS) {
        argv[argc++] = token;
        token = strtok(NULL, " \t\r\n");
    }

    return argc;
}

/*
Les tables "peripherique_ops_t" et "commandes" sont placées dans la section .rodata car elles contient des données constantes (static const).
Par contre peripherique_t est alloué dynamiquement avec malloc donc il est placé dans le tas (heap)
L'indicateur volatile ne change pas la zone memoire utilisé mais le comportement du compilateur pour l'acces a ces variables.
*/
int main(void)
{
    peripherique_t *peripherique = peripherique_creer();

    if (peripherique == NULL) {
        fprintf(stderr,
                "Erreur : impossible de creer le peripherique\n");
        return EXIT_FAILURE;
    }

    const peripherique_ops_t *ops =
        peripherique_get_ops(peripherique);

    contexte_t contexte = {
        .peripherique = peripherique,
        .ops = ops,
        .continuer = 1
    };

    char ligne[256];

    while (contexte.continuer && fgets(ligne, sizeof(ligne), stdin)) {
        char *argv[MAX_ARGUMENTS];

        int argc = decouper_ligne(ligne, argv);

        if (argc == 0) {
            continue;
        }

        const commande_t *commande = trouver_commande(argv[0]);

        if (commande == NULL) {
            printf("Erreur : commande inconnue '%s'\n", argv[0]);
            continue;
        }

        commande->handler(&contexte, argc, argv);
    }

    peripherique_detruire(peripherique);

    return EXIT_SUCCESS;
}