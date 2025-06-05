#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>  // Include this for the exit function

int main() {
    int valeur, ret_fils, etat;

    printf("Je suis le processus pere num=%d \n", getpid());
    valeur = fork();

    switch (valeur) {
    case 0:
        printf("********* FILS *********\n");
        printf("Proc fils num= %d - Pere num= %d\n", getpid(), getppid());
        printf("Je vais dormir 30 secondes ...\n");
        sleep(30);
        printf("Je me reveille, je termine mon execution par un EXIT(7)\n");
        exit(7);  // Correct usage of exit
    case -1:
        printf("Le fork a echoue\n");
        exit(2);  // Correct usage of exit
    default:
        printf("********\n* PERE *\n********\n");
        printf("Proc pere num= %d - Fils num= %d \n", getpid(), valeur);
        printf("J'attends la fin de mon fils: \n");
        ret_fils = wait(&etat);
        printf("Mon fils de num=%d est termine,\nSon etat etait : %d\n", ret_fils, etat);
    }

    return 0;  // Use lowercase 'return'
}

