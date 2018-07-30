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
 * Ultima modifica: 30 luglio 2018, 16.41
 */


#define OCCORRENZE_H
#define LEN 256
static int cw = 0;
static int indice = 0;
int getocc();


int getocc(){
    // Dovra' essere scambiato con swordx.out
    FILE *f1 = fopen("/home/matteo/NetBeansProjects/ProgettoSistemiOperativi/swordx.out", "r+");
    int len;
    char parola[LEN][30]; // Puo' contenere LEN parole e un massimo di 30 caratteri per parola
    int count[LEN];
    int occ = 0;
    int i = 0, j = 0;

    int num_parole = 0;
    int unico = 0;
    if(f1 == NULL){
        printf("File non trovato");
    }
    char arr[LEN]; // Qui salviamo il testo del file
    // Leggi file
    // Setta tutte le celle di count a 0
    for(int c = 0; c < LEN; c++){
        count[c] = 0;
    }
    
    while(fscanf(f1, "%s", arr) != EOF){
        
        len = strlen(arr);
        if(ispunct(arr[len - 1])){
            arr[len - 1] = '\0';
        }
        unico = 1;
        for(i = 0; i < indice && unico; i++){
            if(strcmp(parola[i], arr) == 0){
                unico = 0;
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
        fprintf(f1, "%s => %d\n", parola[i], count[i]);
        printf("%s => %d\n", parola[i], count[i]);
    }

    //printf("Numero parole: %d\n", indice);
    fclose(f1);
    //printf("\nOccorrenze: \n");
    return indice;
    
}
