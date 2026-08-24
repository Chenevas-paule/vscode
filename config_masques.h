#ifndef CONFIG_MASQUES_H
#define CONFIG_MASQUES_H
#include <stdint.h>

uint8_t config_m_construire(unsigned alim, unsigned mode, unsigned canal);

unsigned config_m_alimentation(uint8_t r);
unsigned config_m_mode(uint8_t r);

unsigned config_m_canal(uint8_t r);
#endif