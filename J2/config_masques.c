#include "config_masques.h"

uint8_t config_m_construire(unsigned alim, unsigned mode, unsigned canal)
{
    uint8_t r = 0;
    r |= (alim & 1) << 7;
    r |= (mode & 3) << 5;
    r |= (canal & 7) << 2;
    return r;
}

unsigned config_m_alimentation(uint8_t r){
    return (r >> 7) & 1;
}
unsigned config_m_mode(uint8_t r){
    return (r >> 5) & 3;
}
unsigned config_m_canal(uint8_t r){
    return (r >> 2) & 7;
}