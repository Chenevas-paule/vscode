#include <stdio.h>
/*
Avec PIE :
  LOAD           0x0000000000000000 0x0000000000000000 0x0000000000000000 //adresse de base du segment de code normal avec PIE
  LOAD           0x0000000000001000 0x0000000000001000 0x0000000000001000
  LOAD           0x0000000000002000 0x0000000000002000 0x0000000000002000
  LOAD           0x0000000000002dd0 0x0000000000003dd0 0x0000000000003dd0
Sans PIE :
  LOAD           0x0000000000000000 0x0000000000700000 0x0000000000700000 //adresse de base du segment de code normal sans PIE et -Ttext-segment=0x700000
  LOAD           0x0000000000001000 0x0000000000701000 0x0000000000701000
  LOAD           0x0000000000077000 0x0000000000777000 0x0000000000777000
  LOAD           0x000000000009ee10 0x000000000079fe10 0x000000000079fe10
  */
__attribute__((section(".mes_constantes")))
const int constante = 42;
int main(void){
    printf("salut\n");
    printf("voila\n");
    printf("c'est fini\n");
    return 0;
}
/*
readelf -S deplace :
  [25] .mes_constantes   PROGBITS         0000000000404018  00003018
*/