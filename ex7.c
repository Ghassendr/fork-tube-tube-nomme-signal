#include <stdio.h>
#include <unistd.h>
int main(void)
{
int pid ;
pid = fork();
if (pid==-1)
{ print ("error lors le fork");

if (pid==0)
{
print ( " je suis le fils du pid %d et vais executer ls\n",getpid());
execlp ("ls", "ls" , "-l",NULL);
printf ("s terminer");..
}
else 
{print(" je suuis le pere de processus %d", pid);
}

exit(0);
}}


