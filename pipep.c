#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid_sum, pid_prod;
    char input[100];
    int sum = 0, prod = 1;

     
    printf("Entrez une chaîne de chiffres concaténés : ");
    fgets(input, 100, stdin);
    input[strcspn(input, "\n")] = 0;  // Enlever le caractère de nouvelle ligne de la chaîne

    pid_sum = fork();  // Création du premier processus fils pour la somme

    if (pid_sum < 0) {
        perror("Erreur lors de la création du premier processus");
        exit(1);
    }
    
    if (pid_sum == 0) {
        // Code exécuté par le premier fils (pour la somme)
        int i = 0;
        while (input[i] != '\0') {
            if (input[i] >= '0' && input[i] <= '9') {
                sum += input[i] - '0';  // Convertir le caractère en chiffre et l'ajouter à la somme
            }
            i++;
        }
        exit(sum);  // Le premier fils renvoie la somme
    } else {
        // Création du deuxième processus fils pour le produit
        pid_prod = fork();

        if (pid_prod < 0) {
            perror("Erreur lors de la création du deuxième processus");
            exit(1);
        }

        if (pid_prod == 0) {
            // Code exécuté par le deuxième fils (pour le produit)
            int i = 0;
            while (input[i] != '\0') {
                if (input[i] >= '0' && input[i] <= '9') {
                    prod *= input[i] - '0';  // Convertir le caractère en chiffre et le multiplier
                }
                i++;
            }
            exit(prod);  // Le deuxième fils renvoie le produit
        } else {
            // Code exécuté par le père
            int status_sum, status_prod;
            waitpid(pid_sum, &status_sum, 0);  // Le père attend que le premier fils termine
            waitpid(pid_prod, &status_prod, 0);  // Le père attend que le deuxième fils termine

            if (WIFEXITED(status_sum)) {
                sum = WEXITSTATUS(status_sum);  // Récupère la somme renvoyée par le premier fils
            } else {
                printf("Erreur lors de l'exécution du premier processus fils\n");
            }

            if (WIFEXITED(status_prod)) {
                prod = WEXITSTATUS(status_prod);  // Récupère le produit renvoyé par le deuxième fils
            } else {
                printf("Erreur lors de l'exécution du deuxième processus fils\n");
            }

            // Affichage des résultats
            printf("La somme des chiffres est : %d\n", sum);
            printf("Le produit des chiffres est : %d\n", prod);
        }
    }

    return 0;
}

