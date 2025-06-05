#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid1, pid2, pid3, pid4, pid5;

   
    pid1 = fork();   
    if (pid1 == 0) {
        
        printf("PID: %d, PPID: %d (P2)\n", getpid(), getppid());
        pid4 = fork();  
        if (pid4 == 0) {
            
            printf("PID: %d, PPID: %d (P4)\n", getpid(), getppid());
        }
    } else {
        
        pid3 = fork();   
        if (pid3 == 0) {
             
            printf("PID: %d, PPID: %d (P3)\n", getpid(), getppid());
            pid5 = fork();  
            if (pid5 == 0) {
                 
                printf("PID: %d, PPID: %d (P5)\n", getpid(), getppid());
            }
        }
    }

    if (pid1 > 0 && pid3 > 0) {
        
        printf("PID: %d, PPID: %d (P1)\n", getpid(), getppid());
    }

    return 0;
}

