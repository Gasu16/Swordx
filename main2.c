/* 
 * File:   main.c
 * Author: matteo
 *
 * Created on 14 maggio 2018, 12.32
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * Puntatori
 */
int main(int argc, char** argv) {
    int a = 3;
    int *p = &a; // Puntatore contenente l'indirizzo di a
    
    // Stampa il valore di a
    printf("Valore di a: %d\n", a);
    
    // Stampa l'indirizzo di a
    printf("Indirizzo di a (modo 1): %p\n", (void *)&a); // Modo 1
    printf("Indirizzo di a (modo 2): %p\n", p); // Modo 2
    return 0;
}

