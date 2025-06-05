#include <stdio.h>
#include <unistd.h>
int main()
{
int tube[2];
char buf[20];

pipe(tube);
if (fork()) { /* père */
close (tube[0]);
write (tube[1], "bonjour", 8);
}
else { /* fils */
close (tube[1]);
read (tube[0],buf,8);
printf("%s bien recu ",buf);

}}

