#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

struct capteur {
    
    int  valeur;
    char actif;
    char unite;
    
};

void exo1() {
    struct capteur c;
    printf("Taille de struct capteur : %zu octets\n", sizeof(c));
}

void exo2() {
    int16_t temperature = -15;
    int32_t distance_mm = 384400000;
    uint8_t octet = 250;

    printf("temperature = %" PRId16 "\n", temperature);
    printf("distance_mm = %" PRId32 "\n", distance_mm);
    printf("octet = %" PRIu8 "\n", octet);

    printf("sizeof(int16_t) = %zu octets\n", sizeof(int16_t));
    printf("sizeof(int32_t) = %zu octets\n", sizeof(int32_t));
    printf("sizeof(uint8_t) = %zu octet\n", sizeof(uint8_t));

}

int compter_voyelles(const char* s) {
    int n = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y') n++;
    }
    return n;
}

void exo4() {
    const char* mot = "programmation";
    printf("%d\n", compter_voyelles(mot));  // ne compile pas en l'état : pourquoi 
}

int main(void)
{
    exo4();
    return 0;
}

