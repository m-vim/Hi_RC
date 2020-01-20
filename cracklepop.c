#include <stdio.h>

int main ()
{
   //print 1 to 100 inclusive
   int n;

   for ( n = 1; n <= 100; n++)
   {
       //print "Cracklepop" if n is divisible by both 3 and 5 (will be divisible by 15)
       if ((n % 15) == 0)
       {
           printf("CracklePop\n");
       }
       //print "Crackle" if n is divisible by 3
       else if ((n % 3) == 0)
       {
           printf("Crackle\n");
       }
       //print "Pop" if n is divisible by 5
       else if ((n % 5) == 0)
       {
           printf("Pop\n");
       }
       //print the number if it is not divisble by 3 or 5
       else
       {
           printf("%d\n", n);
       }
   }

   return 0;
}
