/*
this file is used to test key word volatile and sig_atomic_t in c program, and we can use command:
gcc test_volatile.c -g
objectdump -dS a.out
or
insight a.out
we can check the assemble code to look out what changes after we add the key word.
-----------------------------------------------------------------------------------------------------

sig_atomic_t: 
mainly used to avoid multithread compete.
long long t = 3, in 32bit operation software we need two command to execute(high and low assignment)
so we use sig_atomic_t t = 3.

volatile:
this key word invovled compiler optimization.
gcc test_volatile.c -o1 -g
objectdump -dS a.out
we can see the assemble code if we optimized, there woudle dead loop here.

Author: Shouhua Peng
Date: 1/12/2014
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

volatile sig_atomic_t a = 0;

int main()
{
   
   while(!a)
   {
        a = 1;       
   }
   exit(0); 
}
