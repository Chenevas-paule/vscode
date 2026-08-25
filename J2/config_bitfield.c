#include "config_bitfield.h"
#include <stdio.h>

void config_bf_afficher(const struct config_bf *cfg)
{
    printf("Alimentation: %u\n", cfg->alimentation);
    printf("Mode: %u\n", cfg->mode);
    printf("Canal: %u\n", cfg->canal);
}

struct config_bf config_bf_init(unsigned alim, unsigned mode, unsigned canal){
    struct config_bf cfg = {alim, mode, canal};
    return cfg;
}