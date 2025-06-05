#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
int main ( int narg, char*arg[]){
int p[2] , n;
char buffer[256];
if (narg!= 2) {
printf("usage : manque dargument \n");
exit(-1)}
if (pipe (p)==-1){
perror ("Error pipe");
exit(-2)}
if ((n=fork())==-1){
perror ("Errur lors la creation de pros");
exit(-3);}
else if (n==0){
close(1);
dup(p[1]);
close(p[1]);
close(p[0]);
execlp("cat","cat",arg[1],NULL);}
else {
close (0);
dup(p[0]);
close(p[0]);
close(p[1]);
execlp("wc","wc",NULL);}
exit(0);
}



