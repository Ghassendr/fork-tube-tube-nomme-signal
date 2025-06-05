#include <stdio.h>
#include <signal.h>

 
void bonjour(int sig) {
    printf("bonjour\n");
}

 
void bonsoir(int sig) {
    printf("bonsoir\n");
}

 
void quitte(int sig) {
    printf("fin du programme\n");
}

int main() {
    
    signal(SIGUSR1, bonjour);  
    signal(SIGUSR2, bonsoir);   
    signal(SIGQUIT, quitte);    

 
    for(;;);
    
    return 0;
}

