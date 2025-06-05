#include <sys/types.h>
#include <unistd.h>
int main ()
{
int valeur;
valeur = fork();
if (valeur == 0) sleep (4);
printf (" Valeur retournee par la fonction fork:%d\n", valeur);
printf ("Je suis le processus numero %d\n",getpid());
return 0 ;
}
