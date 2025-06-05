#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
Struct sigaction action ;
void hand_sigusr1 (int sig){
printf (" de %d  signal resu \n ",gitpid());
exit(0);}
int main (){
int p,i=0, status;
action.sa_handler=hand_sugusr1;
sigaction (SIGUSR1,&action,NULL);
if ((p=fork())==0){
printf (" je suis le fils du pid %d \n",getpid());
while (1) i=0;
}

}

