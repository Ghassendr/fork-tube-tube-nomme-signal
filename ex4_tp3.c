#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     
#include <sys/types.h>   
#include <sys/wait.h>    
#include <signal.h>     

 
void hand_sigusr1(int sig) {
    printf("de %d) signal SIGUSR1 reçu \n", getpid());
    exit(0);   
}

int main() {
    int p, status;

   
    signal(SIGUSR1, hand_sigusr1);

    if ((p = fork()) == 0) {   
        printf("Je suis le fils du pid %d\n", getpid());
        while (1);  
    }

    printf("Je suis le père de pid %d\n", getpid());

    if (kill(p, 0) == -1) {
        
    } else {
        printf("(de %d) fils %d existant\n", getpid(), p);
        printf("(de %d) envoi du signal SIGUSR1 au processus fils %d\n", getpid(), p);
        kill(p, SIGUSR1); 
    }
 
    p = waitpid(p, &status, 0);
    printf("(de %d) status du fils %d\n", getpid(), p);

    return 0;
}

