/*
Author: Shouhua Peng
Date: 1/17/2014
Description: 
    Funny! This file collected from website is mainly for job interview and from which i learn a lot the book 
can't give.for deal with bit in struct, here is a lot example:
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
Fine! Here is a method to count the number of '1' in a integer by a binary type:
    int count_1(int x)
    {
        int count = 0;
        while(x)
        {
            count++;
            x = x & (x-1);
        }
        return count;
    }
OK, I'm have to disassemble the program to understand why bit->a=1, bit->b=-1, bit->c=-4,
here is assemble code in intel type(gcc bittest.c -g, objdump -dS a.out -M intel):
804845e:    8d 44 24 18             lea    eax,[esp+0x18]
8048462:   89 44 24 1c             mov    DWORD PTR [esp+0x1c],eax
printf("bt->a=%d, bt->b=%d, bt->c=%d\n", bt->a, bt->b, bt->c);
8048466:  8b 44 24 1c             mov    eax,DWORD PTR [esp+0x1c]
804846a: 0f b6 00                movzx  eax,BYTE PTR [eax]
804846d:    c0 f8 05                sar    al,0x5
8048470:   0f be c8                movsx  ecx,al
8048473:  8b 44 24 1c             mov    eax,DWORD PTR [esp+0x1c]
8048477: 0f b6 00                movzx  eax,BYTE PTR [eax]
804847a:    c1 e0 03                shl    eax,0x3
804847d:   c0 f8 06                sar    al,0x6
8048480:  0f be d0                movsx  edx,al
8048483: 8b 44 24 1c             mov    eax,DWORD PTR [esp+0x1c]
8048487:    0f b6 00                movzx  eax,BYTE PTR [eax]
804848a:   c1 e0 05                shl    eax,0x5
804848d:  c0 f8 05                sar    al,0x5
8048490: 0f be c0                movsx  eax,al
8048493:    89 4c 24 0c             mov    DWORD PTR [esp+0xc],ecx
8048497:   89 54 24 08             mov    DWORD PTR [esp+0x8],edx
804849b:  89 44 24 04             mov    DWORD PTR [esp+0x4],eax
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
