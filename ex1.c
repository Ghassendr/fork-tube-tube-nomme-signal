#include <stdio.h>
#include <unistd.h>
int main (){


int pid ;
pid=fork();
if (pid==0)
{
printf("je suis le fils de pid %d je vais exercuter ls ", getpid());
execlp ("ls","ls" ,"-l", NULL);
}
else
{

printf("je suis le pere de pid %d ",pid);
Wait (NULL);
}
}
