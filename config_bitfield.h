
#ifndef CONFIG_BITFIELD_H
#define CONFIG_BITFIELD_H
#include <stdint.h>

struct config_bf{
    unsigned int alimentation : 1;
    unsigned int mode : 2;
    unsigned int canal : 3;
    unsigned int     : 2;
};

void config_bf_afficher(const struct config_bf *cfg);
struct config_bf config_bf_init(unsigned alim, unsigned mode, unsigned canal);

#endif 