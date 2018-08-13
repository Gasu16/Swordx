/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   occorrenze.h
 * Author: matteo
 *
 * Created on 11 luglio 2018, 17.45
 * Ultima modifica: 6 Agosto 2018, 18.13
 */


#define OCCORRENZE_H
#define LEN 256
#include <time.h>
static int cw = 0;
static int indice = 0;
static int ignorate = 0;
int getocc();


int getocc(int argc, char *argv[]){
    clock_t t;
    double cpu_time_used;
    // Dovra' essere scambiato con swordx.out
    //    FILE *fin = fopen("/home/matteo/NetBeansProjects/ProgettoSistemiOperativi/input.txt", "r+");
    FILE *fout = fopen("/home/matteo/NetBeansProjects/ProgettoSistemiOperativi/swordx.out", "r+");
    FILE *flog = fopen("/home/matteo/NetBeansProjects/ProgettoSistemiOperativi/dati.log", "r+");
    t = clock(); // START - Il numero di "tick" di clock trascorsi dall'inizio del programma 
    int len;
    char parola[LEN][30]; // Puo' contenere LEN parole e un massimo di 30 caratteri per parola
    int count[LEN];
    int occ = 0;
    int i = 0, j = 0;
    
    int num_parole = 0;
    int unico = 0;
    if(fout == NULL){
        printf("File non trovato");
    }
    char arr[LEN]; // Qui salviamo il testo del file
    // Leggi file
    // Setta tutte le celle di count a 0
    for(int c = 0; c < LEN; c++){
        count[c] = 0;
    }
    
    
    while(fscanf(fout, "%s", arr) != EOF){
        
        len = strlen(arr);
        if(ispunct(arr[len - 1])){
            arr[len - 1] = '\0'; // Se e' puntato mettiamo il carattere di terminazione
        }
        unico = 1;
        for(i = 0; i < indice && unico; i++){
            if(strcmp(parola[i], arr) == 0){
                unico = 0;
                ignorate++; // Se la parola e' gia' stata trovata allora...
            }
        }
        
        if(unico){
            strcpy(parola[indice], arr);
            count[indice]++;
            indice++;
        }
        else{
            count[i - 1]++;
        }
    }
    int conta;
    for(i = 0; i < indice; i++){
        fprintf(fout, "%s => %d\n", parola[i], count[i]);
        printf("%s => %d\n", parola[i], count[i]);
    }
    
    printf("Numero parole: %d\n", indice);
    printf("Parole ignorate: %d\n", ignorate);
    
    t = clock() - t; // END
    //CLOCKS_PER_SEC ==> Numero di clock del processore per secondo
    cpu_time_used = ((double)t)/CLOCKS_PER_SEC; // In secondi
    double ms = cpu_time_used*1000; // In millisecondi
    printf("Tempo usato: %.3f msec\n", ms);
    
    int contatore;
    int totale = indice + ignorate;
    for(contatore = 2; contatore < argc-1; contatore++){
        
        // Formato stampa: "File" ---- "Parole contate" ---- "Parole ignorate" ---- "Tempo Elab. file"
        fprintf(flog, "\n%s\t%d\t%d\t%.3f msec\n", argv[contatore], indice, ignorate, ms);        
    }
    printf("Totale parole: %d\n", totale);
    
    fclose(flog);
    fclose(fout);
    
    return indice;
}

