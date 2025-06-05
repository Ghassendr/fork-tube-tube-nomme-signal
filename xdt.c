#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SIZE 10
int main() {
    int pipe_fd[2]; 
    pid_t pid;
    if (pipe(pipe_fd) == -1) {
        perror("Erreur lors de la création du pipe");
        exit(EXIT_FAILURE);    } 
    pid = fork();
    if (pid == -1) {
        perror("Erreur lors de la création du processus fils");
        exit(EXIT_FAILURE);}
    if (pid == 0) {  
        close(pipe_fd[1]);  
        int x;
        int tableau[SIZE];
        read(pipe_fd[0], &x, sizeof(int));
        read(pipe_fd[0], tableau, sizeof(int) * SIZE);
        int found = 0;
        for (int i = 0; i < SIZE; i++) {
            if (tableau[i] == x) {
                found = 1;
                break;}
        } 
        if (found) {
            printf("Le nombre %d existe dans le tableau.\n", x);
        } else {
            printf("Le nombre %d n'existe pas dans le tableau.\n", x);
        }
        close(pipe_fd[0]);  
    } else {  
        close(pipe_fd[0]);  
        int tableau[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int x;
        printf("Entrez un nombre à rechercher dans le tableau : ");
        scanf("%d", &x);
        write(pipe_fd[1], &x, sizeof(int));
        write(pipe_fd[1], tableau, sizeof(int) * SIZE);
        close(pipe_fd[1]);  

     
        wait(NULL);
    }

    return 0;
}
