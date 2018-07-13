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
 * Ultima modifica 13 luglio 2018, 19.30
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <argp.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <getopt.h>
#include <dirent.h>
#include "occorrenze.h"


#define LEN 256
#define DIM 256

int opt; // Opzione scelta

const char *short_options = "hrfeamis";
const char *path = "/home/matteo/NetBeansProjects/ProgettoSistemiOperativi/./*";

struct option long_options[] = {
    {"help", no_argument, NULL, 'h'}, // V
    {"recursive", required_argument, NULL, 'r'}, // X
    {"follow", required_argument, NULL, 'f'}, // X
    {"explude", required_argument, NULL, 'e'}, // X
    {"alpha", required_argument, NULL, 'a'}, // X
    {"min", required_argument, NULL, 'm'}, // X
    {"ignore", required_argument, NULL, 'i'}, // X
    {"sortbyoccurrency", required_argument, NULL, 's'}, // X
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
    printf("\n\n");
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

int isDirectory(const char* path){
    struct stat path_stat;
    stat(path, &path_stat);
    if(S_ISDIR(path_stat.st_mode)){
        return 0;
    }
    return 1;
}

void listdir(const char *name, int indent){
    // name: path della directory
    // indent: numero di indentazioni
    DIR *dir; // Directory dove ci troviamo noi
    struct dirent *entry; // Contenuto della directory

    if (!(dir = opendir(name))) // Se non riesce ad aprire la directory usciamo
        return;

    while ((entry = readdir(dir)) != NULL) { // Mentre scorre il contenuto della directory...
        if (entry->d_type == DT_DIR) { // Se il contenuto corrisponde a una directory...
            char bufpath[1024]; // buffer
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)continue;
            
            // snprintf scrive sul buffer specificato bufpath
            snprintf(bufpath, sizeof(bufpath), "%s/%s", name, entry->d_name);            
            
            // stampa la directory e le sue sottodirectory
            printf("%*s[%s]\n", indent, "", entry->d_name); 
            listdir(bufpath, indent + 2); // Ricorsiva...
        } else { // Altrimenti se e' un file...
        //   printf("%*s- %s\n", indent, "", entry->d_name);
        }
    }
    closedir(dir);
}

int main(int argc, char** argv) {    
    
    /* argc: numero di argomenti passati
     * argv: array che contiene gli argomenti passati
     * argv[0]: nome del programma (swordx)
     * argv[1]: primo argomento: opzione
     * argv[2]: secondo argomento: file in input */
    
    FILE *file = fopen(argv[2], "r"); // File di input
    FILE *fileOUTPUT = fopen("swordx.out", "w+"); // File di output
    
    
    while((opt = getopt_long(argc, argv, short_options, long_options, NULL)) != -1){
        switch(opt){
            case 'h':
                getHelp();    
            //    splitFile(file, fileOUTPUT); // ./swordx -h input.txt swordx.out
                break;
            case 'r':
                printf("\nRecursive\n");
                listdir(".", 0);
                
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

