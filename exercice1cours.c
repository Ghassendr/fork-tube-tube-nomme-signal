#include <stdio.h>
#include <unistd.h>
int main (void){
int tube [2];
unsigned char buffer [256];
int i;
printf("creation de tube ");
if (pipe (tube)!=0){
perror ("pipe");
}
for (i=0;i<256;i++)
buffer [i]=i;
if (write (tube[1],buffer,256)!=256){
perror("write");
exit(1);
}

printf("lecture depuis tube ");

if (read (tube[0],buffer,256)!=256){
perror("read");
exit(1);
}

printf ("verification ");
for (i=0; i<256;i++){
if (buffer [i]!= i) {
printf("buffer error %d : %d",i, buffer[i]);
exit(1);

}}
printf("ok");
return (0);
}
