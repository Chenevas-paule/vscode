#include "parseur_entete.h"
#include <stdio.h>
void parser_entete(const uint8_t buffer[8], struct entete *out)
{
    out->version_majeure = (buffer[0] & 0xF0) >> 4;
    out->version_mineure = buffer[0] & 0x0F;

    out->compresse = (buffer[1] & 0x01) != 0;
    out->chiffre   = (buffer[1] & 0x02) != 0;

    out->type_message = ((uint16_t)buffer[2] << 8) | (uint16_t)buffer[3];

    out->taille_payload = ((uint32_t)buffer[4] << 24) | ((uint32_t)buffer[5] << 16) | ((uint32_t)buffer[6] << 8) | (uint32_t)buffer[7];
}

void afficher_entete(const struct entete *e){
    printf("Version : %u.%u\n", e->version_majeure, e->version_mineure);
    printf("Compresse : %d\n", e->compresse);
    printf("Chiffre : %d\n", e->chiffre);
    printf("Type de message : 0x%04X\n", e->type_message);
    printf("Taille du payload : %u\n", e->taille_payload);
}