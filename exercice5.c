#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipe_fils_to_pere[2]; // Pipe pour envoyer du fils au père
    int pipe_pere_to_fils[2]; // Pipe pour envoyer du père au fils
    pid_t pid;

    // Création des pipes
    if (pipe(pipe_fils_to_pere) == -1 || pipe(pipe_pere_to_fils) == -1) {
        perror("Erreur lors de la création des pipes");
        exit(EXIT_FAILURE);
    }

    // Création du processus fils
    pid = fork();

    if (pid < 0) {
        perror("Erreur lors de fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Code du processus fils
        // Fermeture des extrémités inutilisées des pipes
        close(pipe_fils_to_pere[0]); // Non utilisé par le fils
        close(pipe_pere_to_fils[1]); // Non utilisé par le fils

        // Affichage des entiers impairs
        for (int i = 1; i <= 99; i += 2) {
            // Attendre que le père ait affiché un nombre pair
            write(pipe_fils_to_pere[1], &i, sizeof(i));
            // Lire pour signaler au père qu'il peut afficher un nombre pair
            read(pipe_pere_to_fils[0], &i, sizeof(i));
        }
        // Fermeture des pipes
        close(pipe_fils_to_pere[1]);
        close(pipe_pere_to_fils[0]);
        exit(EXIT_SUCCESS);
    } else { // Code du processus père
        // Fermeture des extrémités inutilisées des pipes
        close(pipe_fils_to_pere[1]); // Non utilisé par le père
        close(pipe_pere_to_fils[0]); // Non utilisé par le père

        // Affichage des entiers pairs
        for (int i = 2; i <= 100; i += 2) {
            // Lire pour recevoir un nombre impair du fils
            read(pipe_fils_to_pere[0], &i, sizeof(i));
            printf("Fils : %d\n", i); // Affichage du nombre impair
            // Envoyer un nombre pair au fils pour lui indiquer de continuer
            write(pipe_pere_to_fils[1], &i, sizeof(i));
        }
        // Fermeture des pipes
        close(pipe_fils_to_pere[0]);
        close(pipe_pere_to_fils[1]);
        wait(NULL); // Attendre que le processus fils se termine
        exit(EXIT_SUCCESS);
    }
}

