/*
This file is aimed to test the variable arguments in c environment.
We mainly use data structure which defined in head file stdarg.h as follows:
va_list pvar;
va_start(pvar, parmN);
va_arg(pvar, type);
va_end(pvar);
we can use command "man vprintf" to check the details.
********************************************************************************
Author: Shouhua Peng
Date: 1/12/2014
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char *make_message(const char *fmt, ...)
{
    int n;
    int size = 100;
    char *p, *np;
    va_list ap;
    if((p=malloc(size)) == NULL)
        return NULL;
    while(1)
    {
        va_start(ap, fmt);
        n = vsnprintf(p, size, fmt, ap);
        va_end(ap);
        if(n<0)
            return NULL;
        if(n<size)
            return p;
        size = n + 1;
        if((np = realloc(p, size)) == NULL)
        {
            free(p);
            return NULL;
        }
        else
            p = np;
    }
}

int main()
{
    char *msg = make_message("%s's message is: %s", "shouhua", "Hello, world!");
    printf("%s\n", msg);
    exit(0);
}
