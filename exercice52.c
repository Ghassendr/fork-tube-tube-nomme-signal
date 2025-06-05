#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

pid_t child_pid; // PID du processus fils
pid_t parent_pid; // PID du processus père

// Gestionnaire pour le processus père
void handler_pere(int sig) {
    static int num = 2;
    if (num <= 100) {
        printf("Père : %d", num);
        fflush(stdout);
        num += 2;
        kill(child_pid, SIGUSR1); // Envoyer un signal au fils
    } else {
        exit(EXIT_SUCCESS); // Terminer le processus père
    }
}

// Gestionnaire pour le processus fils
void handler_fils(int sig) {
    static int num = 1;
    if (num <= 99) {
        printf("Fils : %d", num);
        fflush(stdout);
        num += 2;
        kill(parent_pid, SIGUSR1); // Envoyer un signal au père
    } else {
        exit(EXIT_SUCCESS); // Terminer le processus fils
    }
}

int main() {
    // Enregistrer les PID du père
    parent_pid = getpid();

    // Créer un processus fils
    child_pid = fork();

    if (child_pid < 0) {
        perror("Erreur lors de la création du processus fils");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {

// Code du fils
        signal(SIGUSR1, handler_fils); // Installer le gestionnaire de signal pour le fils

        kill(parent_pid, SIGUSR1);     // Initialiser le signal vers le père
sleep(5);
        while (1) pause();            // Attendre les signaux
    } else { // Code du père
        signal(SIGUSR1, handler_pere); // Installer le gestionnaire de signal pour le père
        while (1) pause();            // Attendre les signaux
    }

    return 0;
}
