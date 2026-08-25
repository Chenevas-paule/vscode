#include <stdio.h>
#include <stddef.h>

typedef struct {
    const char *nom;
    void (*fonction)(void);
} handler_t;

void job_calcul(void)
{
    printf("job_calcul appelee\n");
}

void job_recuperation(void)
{
    printf("job_recuperation appelee\n");
}

void job_affichage(void)
{
    printf("job_affichage appelee\n");
}

void job_ajout(void)
{
    printf("job_ajout appelee\n");
}

static const handler_t handler_c
    __attribute__((used, section("mes_handlers"))) = {"job_calcul", job_calcul};

static const handler_t handler_r
    __attribute__((used, section("mes_handlers"))) = {"job_recuperation", job_recuperation};

static const handler_t handler_a
    __attribute__((used, section("mes_handlers"))) = {"job_affichage", job_affichage};

static const handler_t handler_j
    __attribute__((used, section("mes_handlers"))) = {"job_ajout", job_ajout};


extern const handler_t __start_mes_handlers[];
extern const handler_t __stop_mes_handlers[];

int main(void)
{
    const handler_t *debut = __start_mes_handlers;
    const handler_t *fin = __stop_mes_handlers;

    size_t nombre = (size_t)(fin - debut);

    printf("Nombre de handlers : %zu\n", nombre);

    for (const handler_t *h = debut; h < fin; h++) {
        printf("Handler : %s\n", h->nom);
        h->fonction();
    }

    return 0;
}

/*
Q7 :
  [26] mes_handlers      PROGBITS         0000000000004020  00003020
       0000000000000030  0000000000000000  WA       0     0     16

    0000000000004020 D __start_mes_handlers
    0000000000004050 D __stop_mes_handlers

Q8:
__attribute__((used)) indique au compilateur que ces variables doivent être conservées 
l'optimisation (-O2) du compilateur peut considérer les variables static const comme inutilisées et les supprimer.

 Q9:
L'ordre observé avec nm/readelf n'est pas une garantie du langague mais un effet de l'ordre de liaison 
 on ne doit pas s'appuyé sur cela dans un programme
 */