#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LEN 256

int main(int argc, char** argv) {
    FILE *f1 = fopen("test1.txt", "r");
    int len;
    char parola[LEN][30]; // Puo' contenere LEN parole e un massimo di 30 caratteri per parola
    int count[LEN];
    int occ = 0;
    int i = 0, j = 0;
    int index = 0;
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
        for(i = 0; i < index && unico; i++){
            if(strcmp(parola[i], arr) == 0){
                unico = 0;
            }
        }
        
        if(unico){
            strcpy(parola[index], arr);
            count[index]++;
            index++;
        }
        else{
            count[i - 1]++;
        }
    }
    
    fclose(f1);
    printf("Occorrenze: \n");
    for(i = 0; i < index; i++){
        printf("%s => %d\n", parola[i], count[i]);
    }
    
    return 0;
}

