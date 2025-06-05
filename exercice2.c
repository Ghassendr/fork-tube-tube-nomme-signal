#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
int tube [2];
int pid;
char buffer [32];
int status;

if (pipe(tube)==-1 ){
printf("error lors de creation de tube");
exit(-1);
}
 if ((pid=fork()) ==-1){
printf("erreur lors de fork");
exit(-1);
}

else if (pid==0){
close(tube[0]);
write(tube[1],"je suis le fils",16);
exit(0);
}
else  {
close (tube[1]);
read(tube[0],buffer, 16);
printf("pere : message <%s > recu \n",buffer );
wait(&status);
}

}
