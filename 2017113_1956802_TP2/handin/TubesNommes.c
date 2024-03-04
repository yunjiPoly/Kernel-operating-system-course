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
    
    mkfifo("Tube",0660);
    if(fork() == 0) { //P3 cmp- In.txt-s

        if(fork() == 0) {//P2 rev
        
        if(fork() == 0) {//P1 rev < In.txt
        //lire
        int fd = open("Tube",O_WRONLY);
        //int tmp = open("./In.txt", O_RDONLY);
        dup2(fd,1);//STDOUT_FILENO
        //dup2(fd,0);//STDIN_FILENO
        close(fd);
        execlp("rev","rev","In.txt",NULL);
        _exit(0);

        }
        
        execlp("rev","rev",NULL);
        _exit(0);

        }
        execlp("cmp","cmp","-","In.txt","-s",NULL);
        _exit(0);
    
}
}