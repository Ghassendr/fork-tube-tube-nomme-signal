#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
pid_t pid_fils;
void signal_pere(int sig) {
    static int pair = 2;
    if (pair <= 100) {
        printf(" Pere: %d ", pair);
         fflush(stdout);
        pair += 2;
        kill(pid_fils, SIGUSR1);  
    } else {
        exit(0);   }}
void signal_fils(int sig) {  
    static int impair = 1;
    if (impair <= 99) {
        printf(" Fils: %d ", impair);
          fflush(stdout);
        impair += 2;
        kill(getppid(), SIGUSR1);  
    } else {
        exit(0);  }}
int main() {
    pid_fils = fork();
    if (pid_fils < 0) {
        perror("Erreur");
        exit(1); }
    if (pid_fils == 0) {         
        signal(SIGUSR1, signal_fils);  
        while (1) pause(); 
    } else {
        signal(SIGUSR1, signal_pere);   
        printf (" ");    
          fflush(stdout);
        kill(pid_fils, SIGUSR1);  
        while (1) pause();  }
    return 0;}
