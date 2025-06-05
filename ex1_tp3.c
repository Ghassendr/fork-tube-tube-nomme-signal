#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>  
#include <stdlib.h>   

 
int main(void) 
{ 
    int pid; 
    pid = fork(); 
    if (pid == 0)  
    { 
        printf("je suis le fils du pid %d et vais exécuter ls\n", getpid()); 
        execlp("ls", "ls", "-l", NULL);  
    } 
    else  
    { 
        printf("je suis le père du processus %d\n", pid);
        wait(NULL);  
    } 
    exit(0); 
}

