/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   swordx.c
 * Author: matteo
 *
 * Created on 25 giugno 2018, 12.01
 * Ultima modifica 30 giugno 2018, 13.10
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <argp.h>
#include <sys/stat.h>
#include <getopt.h>
#include <glob.h>
#include "occorrenze.h"

#define LEN 256
#define DIM 256

int opt; // Opzione scelta

const char *short_options = "hrfeamis";
const char *path = "/home/matteo/NetBeansProjects/ProgettoSistemiOperativi/./*";

struct option long_options[] = {
    {"help", no_argument, NULL, 'h'}, // FATTO
    {"recursive", required_argument, NULL, 'r'},
    {"follow", required_argument, NULL, 'f'},
    {"explude", required_argument, NULL, 'e'},
    {"alpha", required_argument, NULL, 'a'},
    {"min", required_argument, NULL, 'm'},
    {"ignore", required_argument, NULL, 'i'},
    {"sortbyoccurrency", required_argument, NULL, 's'},
    {NULL, 0, NULL, 0} // Controllo della fine della struttura
};

void getHelp(){
    /* Apriamo il file help.txt (ovviamente deve essere nella stessa directory
     di questo programma) */
    FILE *fhelp = fopen("help.txt", "r");
    char testodaleggere[DIM]; // Testo del file help.txt
    if(fhelp == NULL){ // Se non e' presente il file nella stessa directory...
        printf("File non trovato\n");
        exit(EXIT_FAILURE); // System call
    }
    fseek(fhelp, 0, SEEK_SET); // Resettiamo il puntatore a zero per leggere il file dall'inizio
    
    while(fscanf(fhelp, "%s", &testodaleggere) != EOF){
        /* Quello che andiamo a leggere da file lo metto in "testodaleggere" 
         fin quando arrivo a EOF (end of file) */
        printf(" %s", testodaleggere);
    }
    
}

void leggiFile(FILE *file){
    char text[DIM]; // Testo da leggere
    char *sp;
    char *cp;
    if(file == NULL){ // Controlla se il file e' presente nella stessa directory
        printf("File mancante\n");
        exit(EXIT_FAILURE);
    }
    fseek(file, 0, SEEK_SET); // Metti il puntatore a 0 cosi' legge dall'inizio del file
    while(fscanf(file, "%s", &text) != EOF){ // Legge fino alla fine del file (EOF)
        //    printf(" %s", text); // Stampa il testo normale
        cp = &text;
        sp = strtok(cp, " ,.-?");
        printf("%s\n", sp); // Stampa il testo splittato (sul file rimane scritto normale)
    }
}

void scriviFile(FILE *fileIN, FILE *fileOUT){ // File di input e file di output
    char stringa[DIM]; // Testo da scrivere sul file di output
    char str[DIM]; // Testo da leggere sul file di output
    char array[DIM];
    
    if(fileIN == NULL){ // Controlla se il file e' presente nella stessa directory
        printf("File di input mancante\n");
        exit(EXIT_FAILURE);
    }
    if(fileOUT == NULL){ // Controlla se il file e' presente nella stessa directory
        printf("File di output mancante\n");
        exit(EXIT_FAILURE);
    }
    
    
    // Copia il contenuto di fileIN su fileOUT
    int a;
    while((a = fgetc(fileIN)) != EOF){
        fputc(a, fileOUT);
    }
    
    
    //    fgets(stringa, DIM, stdin); // Salviamo quello che scriviamo in stringa
    //    fprintf(fileOUT, stringa); // Scriviamo la stringa su fileOUT
    leggiFile(fileOUT); // leggiamo il contenuto di fileOUT
}

void splitFile(FILE *fileIN, FILE *fileOUT){
    // split words
    
    char array[DIM];
    
    //    printf("File input: \n");
    //    scriviFile(file, fileOUTPUT);
    /*
     splitFile(file, fileOUTPUT); // L'output dovra' essere per forza splittato (swordx.out)
     */   
    fseek(fileIN, 0, SEEK_SET);
    while(fscanf(fileIN, "%s", array) != EOF){
        printf("%s\n", array);
        fprintf(fileOUT, "%s\n", array);
    }
    fclose(fileIN);
    fclose(fileOUT);
    
}



int main(int argc, char** argv) {    
    
    /* argc: numero di argomenti passati
     * argv: array che contiene gli argomenti passati
     * argv[0]: nome del programma (swordx)
     * argv[1]: primo argomento: opzione
     * argv[2]: secondo argomento: file in input */
    
    //    printf("BENVENUTO");
    FILE *file = fopen(argv[2], "r"); // File di input
    FILE *fileOUTPUT = fopen("swordx.out", "w+"); // File di output
    
    
    while((opt = getopt_long(argc, argv, short_options, long_options, NULL)) != -1){
        switch(opt){
            case 'h':
                getHelp();    
                break;
            case 'r':
                /*
                 printf("\nRecursive\n");
                 glob_t pglob;
                 glob(path, GLOB_ONLYDIR, NULL, &pglob);
                 printf("Trovati %d risultati\n", pglob.gl_pathc);
                 int i;
                 for(i = 0; i < pglob.gl_pathc; i++){
                 printf("File %d: %s\n", i+1, pglob.gl_pathv[i]); // Lista le sottodirectory
                 }
                 globfree(&pglob);
                 */
                break;
            case 'f':
                printf("\nFollow\n");
                break;
            case 'e':
                printf("\nExplude\n");
                break;
            case 'a':
                printf("\nAlpha\n");
                break;
            case 'm':
                printf("\nMin\n");
                break;
            case 'i':
                printf("\nIgnore\n");
                break;
            case 's':
                printf("\nSort by occurrency\n");
                break;
                
        }
    }
    getocc();
    
    return 0;
}

