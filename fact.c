#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

 
unsigned long long factorial(int n) {
    if (n == 0 || n == 1) return 1;
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}
int main() {
    int pipe1[2], pipe2[2];  
    pid_t pid1, pid2;

 
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("erreur loos  la creation des pipe");
        exit(1);
    }
 
    pid1 = fork();
    if (pid1 == -1) {
        perror("Erreur lors fork fils1");
        exit(EXIT_FAILURE);}

    if (pid1 == 0) { 
        close(pipe1[1]);  
        close(pipe2[0]); 

        int number;
        read(pipe1[0], &number, sizeof(int));  

        unsigned long long fact = factorial(number);  
        write(pipe2[1], &fact, sizeof(unsigned long long));  

        close(pipe1[0]); 
        close(pipe2[1]);  

        exit(0);
    }

    
    pid2 = fork();
    if (pid2 == -1) {
        perror("Erreur lors de la création du processus fils2");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {  
        close(pipe1[0]);  
        close(pipe1[1]);
        close(pipe2[1]);  

        unsigned long long fact;
        read(pipe2[0], &fact, sizeof(unsigned long long));  

        printf("Le second fils affiche la factorielle : %llu\n", fact);  
        close(pipe2[0]);  

        exit(0);
    }

     
    close(pipe1[0]);  
    close(pipe2[0]);  
    close(pipe2[1]);

    srand(getpid());
    int random_number = rand() % 10 + 1;  
    printf("Le père envoie le nombre : %d\n", random_number);

    write(pipe1[1], &random_number, sizeof(int)); 

    close(pipe1[1]); 

    
    wait(NULL);
    wait(NULL);

    return 0;
}
