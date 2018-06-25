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
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <argp.h>
#include <sys/stat.h>
#define DIM 256

void getHelp(){
    FILE *fhelp = fopen("help.txt", "r");
    char testodaleggere[DIM];
    if(fhelp == NULL){
        printf("File non trovato\n");
        exit(EXIT_FAILURE); // System call
    }
    fseek(fhelp, 0, SEEK_SET);
    while(fscanf(fhelp, "%s", &testodaleggere) != EOF){
        printf(" %s", testodaleggere);
    }
    
}


int main(int argc, char** argv) {    
    
    FILE *file = fopen(argv[2], "r");
    // Effettuiamo i controlli dei parametri da passare
   
    
    /***** HELP *****/
    
    if((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "-help") == 0)){
        getHelp();
    }
    
    /***** RECURSIVE *****/
    if((strcmp(argv[1], "-r") == 0) || (strcmp(argv[1], "-recursive") == 0)){
        printf("Recursive\n");
    }
    
    /***** FOLLOW *****/
    if((strcmp(argv[1], "-f") == 0) || (strcmp(argv[1], "-follow") == 0)){
        printf("Follow\n");
    }
    
    /***** EXPLUDE *****/
    if((strcmp(argv[1], "-e") == 0) || (strcmp(argv[1], "-explude") == 0)){
        printf("Explude\n");
    }
    
    /***** ALPHA *****/
    if((strcmp(argv[1], "-a") == 0) || (strcmp(argv[1], "-alpha") == 0)){
        printf("Alpha\n");
    }
    
    /***** MIN *****/
    if((strcmp(argv[1], "-m") == 0) || (strcmp(argv[1], "-min") == 0)){
        printf("Min\n");
    }
    
    /***** IGNORE *****/
    if((strcmp(argv[1], "-i") == 0) || (strcmp(argv[1], "-ignore") == 0)){
        printf("Ignore\n");
    }
    
    /***** SORTBYOCCURRENCY *****/
    if((strcmp(argv[1], "-s") == 0) || (strcmp(argv[1], "-sortbyoccurrency") == 0)){
        printf("Sort by occurrency\n");
    }
    return 0;
}

