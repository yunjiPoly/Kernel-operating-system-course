// ajouter les directives d'inclusion nécessaires
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
int main() {
    int fd[2];
    //pid_t cpid;
    //char buf;

    //cpid = fork();
    pipe(fd);//Tube anonyme
    if(fork() == 0) { //P3 cmp- In.txt-s

        if(fork() == 0) {//P2 rev
        
        if(fork() == 0) {//P1 rev < In.txt
        //lire
        close(fd[0]);
        int tmp = open("./In.txt", O_RDONLY);
        dup2(fd[1],STDIN_FILENO);//STDOUT_FILENO
        dup2(tmp,STDOUT_FILENO);//STDIN_FILENO
        close(fd[1]);
        execlp("rev","rev",NULL);
        _exit(0);

        }
        //wait(NULL);
        dup2(fd[0],0);
        //close(fd[0]); 
        dup2(fd[1],1);
        close(fd[1]);
        execlp("rev","rev",NULL);
        _exit(0);

        }

        close(fd[0]);
        close(fd[1]);
        execlp("cmp","cmp","-","In.txt","-s",NULL);
        _exit(0);

    }



    
}
//Affichage de cmp a faire pour voir la bonne valeur
