#ifndef PARSEUR_ENTETE_H
#define PARSEUR_ENTETE_H
#include <stdint.h>

struct entete { unsigned version_majeure, version_mineure; int compresse, chiffre; uint16_t type_message; uint32_t taille_payload; };
/* Parse les 8 premiers octets de buffer (suppose buffer de taille >= 8) et remplit *out. */
void parser_entete(const uint8_t buffer[8], struct entete *out);

void afficher_entete(const struct entete *e);
#endif