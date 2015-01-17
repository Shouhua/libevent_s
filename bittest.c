/*
Author: Shouhua Peng
Date: 1/17/2014
Description: 
    Funny! This file collected from website is mainly for job interview and from which i learn a lot the book can't give.
for deal with bit in struct, here is a lot example:
    struct BIT{
        int a:3;
        int b:2;
        int :0;  // this line is to cause varible c stored in next memory cell, 32~36(c)
        int c:5;
        int :1;  // this line is to cause varible d stored in memory cell 38~39
        int d:2; 
        }
Great! Here is a ideal is used swap two integer varible with intemdiate varible:
    a ^= b;
    b ^= a;
    a ^= b;
*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct BIT
{
    int a:3;
    int b:2;
    int c:3;
}bit;

void last_fun(void)
{
    printf("This function is executed after main exit!\n");    
}

int main()
{
    int i;
    int b = 0x99;
    bit *bt = (bit *)(&b);
    i = atexit(last_fun);    // test function atexit
    if(i != 0)
    {
        fprintf(stderr, "can't set atexit function\n");
        exit(EXIT_FAILURE);
    }
    printf("sizeof bit is %d\n", sizeof(bit));
    printf("a=%d, b=%d, c=%d\n", bt->a, bt->b, bt->c);
    printf("We will exit from main with success\n");
    exit(EXIT_SUCCESS);    
}
