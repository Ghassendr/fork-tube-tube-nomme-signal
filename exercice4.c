#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
int main(int narg, char *arg[]) {
    int p[2];
    pid_t n;
    if (narg != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", arg[0]);
        exit(EXIT_FAILURE);}
    if (pipe(p) == -1) { 
        perror("Erreur pipe");
        exit(EXIT_FAILURE);    }
    if ((n = fork()) == -1) {  
        perror("Erreur fork");
        exit(EXIT_FAILURE);
    } else if (n == 0) {
        close(p[0]);          
        dup2(p[1], STDOUT_FILENO);  
        close(p[1]);          
        execlp("ls", "ls", arg[1], NULL);
        perror("Erreur execlp ls");
        exit(EXIT_FAILURE);
    } else {
        close(p[1]);           
        dup2(p[0], STDIN_FILENO); 
        close(p[0]);         
        execlp("sort", "sort", "-r", NULL);
        perror("Erreur execlp sort");
        exit(EXIT_FAILURE); }
    return 0;  
}
 
