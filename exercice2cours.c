#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main( void){
int tube [2];
int i;
int fils1 ;
unsigned char buffer [256];
if ((pipe(tube))!=0){
perror("error lors de la creation");
exit(1);
}if ((fils1=fork())==-1){
perror("erreur lors de la creation");
}
else 
if (fils1==0){
printf ("fils va lire");
close (tube[1]);
if (read (tube[0],buffer,256)!=256){
perror("probleme de read");
exit(1);}
for (i=0;i<256;i++){
printf ("%d", buffer[i]);}
}
else 
{printf ("pere ecrit ");
for (i=0;i<256;i++){ buffer[i]=i;}
close (tube[0]);
if (write (tube[1],buffer,256)!=256){
perror("probleme de write");
exit(1);}
wait(NULL);
}
return(0);

}

