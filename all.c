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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
int main ( int narg, char*arg[]){
int p[2] , n;
char buffer[256];
if (narg!= 2) {
printf("usage : manque dargument \n");
exit(-1)}
if (pipe (p)==-1){
perror ("Error pipe");
exit(-2)}
if ((n=fork())==-1){
perror ("Errur lors la creation de pros");
exit(-3);}
else if (n==0){
close(1);
dup(p[1]);
close(p[1]);
close(p[0]);
execlp("cat","cat",arg[1],NULL);}
else {
close (0);
dup(p[0]);
close(p[0]);
close(p[1]);
execlp("wc","wc",NULL);}
exit(0);
}





#include <stdio.h>
#include <signal.h>
 
void bonjour (int sig){
printf("bonjour\n");
}
void bonsoir( int sig){
printf("bonsoir\n");
}
void quitte( int sig){
printf("fin du programme\n");
}
int main() {
signal(SIGUSR1, bonjour);
signal(SIGUSR2, bonsoir);
signal(SIGQUIT, quitte); 
for(;;);
}

