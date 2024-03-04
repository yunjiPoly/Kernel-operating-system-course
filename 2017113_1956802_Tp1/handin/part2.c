/*
 * Clone Lab - part2.c
 * 
 * Ecole polytechnique de Montreal, 2018
 */

#include "libprocesslab.h"
#include <stdio.h>

// TODO
// Si besoin, ajouter ici les directives d'inclusion
// -------------------------------------------------
#include <unistd.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
// -------------------------------------------------

#define PART2_OUTPUT_FILE_PATH "part2Output.txt"

void part2() {
    // Ouverture du fichier de sortie pour la question 2.3
    FILE* part2OutputFile = fopen(PART2_OUTPUT_FILE_PATH, "a");
    char tokens[100] = "60392bd4c0d0b6255ed01936";
    int level0 = getpid();
    char buffer[256];
    sprintf(buffer,"%d",level0);//write pid sur buffer ( %d = type (int))
    fprintf(part2OutputFile,"Root process has pid %d (message from process ",level0);//level0

    // code a level 0
    if(fork() == 0){
        // code a 1.1
        if(fork()==0){
            // code a 2.1
            registerProc(2, 1, getpid(),  getppid());
            execl("./part2/level2.1","level2.1",buffer,NULL);
            exit(0);
        }
        if(fork()==0){
            // code a 2.2
            registerProc(2, 2, getpid(),  getppid());
            execl("./part2/level2.2","level2.2",buffer,NULL);
            exit(0);
        }
        
        registerProc(1, 1, getpid(), getppid());
        fprintf(part2OutputFile,"level1.1)\n");
        fclose(part2OutputFile);
        execl("./part2/level1.1","level1.1",buffer,NULL);
        while(wait(NULL)>0); // cree 1.1
        exit(0);
    } 
    

    if ( fork()==0){
        //1.2

         if(fork()==0){
            // code a 2.3
            registerProc(2, 3, getpid(), getppid());
            fprintf(part2OutputFile,"level2.3)\n");
            fclose(part2OutputFile);
            execl("./part2/level2.3","level2.3",buffer,NULL);
            exit(0);
        }
       
        registerProc(1, 2, getpid(), getppid());
        execl("./part2/level1.2","level1.2",buffer,NULL);
        while(wait(NULL)>0); // cree 1.2
        exit(0);
    }
   

    if(fork() == 0){
        // code a 1.3
       if(fork()==0){
            // code a 2.4
            registerProc(2, 4, getpid(),  getppid());
            fprintf(part2OutputFile,"level2.4)\n");
            fclose(part2OutputFile);
            execl("./part2/level2.4","level2.4",buffer,NULL);
            exit(0);
        }
        if(fork()==0){
            // code a 2.5
             registerProc(2, 5, getpid(),  getppid());
            fprintf(part2OutputFile,"level2.5)\n");
            fclose(part2OutputFile);
            execl("./part2/level2.5","level2.5",buffer,NULL);
            exit(0);
        }
        
        if(fork()==0){
            // code a 2.6
            registerProc(2, 6, getpid(),  getppid());
            execl("./part2/level2.6","level2.6",buffer,NULL);
            exit(0);
        }
               
        registerProc(1, 3, getpid(), getppid());
        fprintf(part2OutputFile,"level1.3)\n");
        fclose(part2OutputFile);
        execl("./part2/level1.3","level1.3",buffer,NULL);     
        wait(NULL);// cree 1.3
        exit(0);
    } 
    
    fprintf(part2OutputFile, "level0)\n");
    fclose(part2OutputFile);
    while(wait(NULL)>0);//execute 2.1, 2.2 ... 
    exit(0);   
}