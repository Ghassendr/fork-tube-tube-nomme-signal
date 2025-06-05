#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid_sum, pid_prod;
    char input[100];
    char result_sum[10], result_prod[10];

    int pipe_sum[2], pipe_prod[2];

    if (pipe(pipe_sum) == -1 || pipe(pipe_prod) == -1) {
        perror("Erreur lors de la création des tubes");
        exit(1);
    }

    printf("Entrez une chaîne de chiffres concaténés : ");
    fgets(input, 100, stdin);
    input[strcspn(input, "\n")] = 0;

    pid_sum = fork();

    if (pid_sum < 0) {
        perror("Erreur lors de la création du premier processus");
        exit(1);
    }

    if (pid_sum == 0) {
       
        close(pipe_sum[0]); 
        int sum = 0;

        for (int i = 0; input[i] != '\0'; i++) {
            if (input[i] >= '0' && input[i] <= '9') {
                sum += input[i] - '0';  
            }
        }

        char somch[10];
        sprintf(somch, "%d", sum);  
        write(pipe_sum[1], somch, strlen(somch) + 1); 
        close(pipe_sum[1]); 
        exit(0);
    } else {
        pid_prod = fork();

        if (pid_prod < 0) {
            perror("Erreur lors de la création du deuxième processus");
            exit(1);
        }

        if (pid_prod == 0) {
            
            close(pipe_prod[0]);  
            int prod = 1;

            for (int i = 0; input[i] != '\0'; i++) {
                if (input[i] >= '0' && input[i] <= '9') {
                    prod *= input[i] - '0';  
                }
            }

            char prodch[10];
            sprintf(prodch, "%d", prod); 
            write(pipe_prod[1], prodch, strlen(prodch) + 1);  
            close(pipe_prod[1]); 
            exit(0);
        } else {
             
            close(pipe_sum[1]);  
            close(pipe_prod[1]);  

            wait(NULL);  
            wait(NULL);  

            read(pipe_sum[0], result_sum, sizeof(result_sum));  
            read(pipe_prod[0], result_prod, sizeof(result_prod));  

            printf("La somme des chiffres est : %s\n", result_sum);
            printf("Le produit des chiffres est : %s\n", result_prod);

            close(pipe_sum[0]); 
            close(pipe_prod[0]);  
        }
    }

    return 0;
}

