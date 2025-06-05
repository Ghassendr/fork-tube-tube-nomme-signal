#include <stdio.h>
#include <unistd.h> 
int main(int argc , char*argv[]) {
if (argc<2){
printf(" 2 args recuired");
exit(1);}
execvp(argv[1],&argv[1]);
return 0; 

}
