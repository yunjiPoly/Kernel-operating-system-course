/*
 * Init Lab - q1.c
 * 
 * Ecole polytechnique de Montreal, 2018
 */

// TODO
// Si besoin, ajouter ici les directives d'inclusion
// -------------------------------------------------
#include <string.h>
#include <unistd.h>
#include <stdio.h>
// -------------------------------------------------

/*
 * Vous devez imprimer le message indiqué dans l'énoncé:
 * - En exécutant un premier appel à printf AVANT l'appel à write
 * - Sans utiliser la fonction fflush
 * - En terminant chaque ligne par le caractère '\n' de fin de ligne
 */
void question1() {
    // TODO
    printf("90c630811fd2001c8579d85044165482 (printed using printf)");
    write(STDOUT_FILENO,"90c630811fd2001c8579d85044165482 (printed using write)\n",strlen ("44b014bef71345075b78cb1d6402e4f0 (printed using write)\n"));
    printf("\n");

}