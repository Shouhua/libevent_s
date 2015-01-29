/*
1. About printf format:
    Actually, in manual file there have exactly clear explain, i just summarize it in my perspective.
if your want to printf characters, first of all '%' is needed, after that is as fllows:
    %[#,0,-,' ',+][field width(number)][.number][l,h...(length modifier)][d,f,s,c,%...(conversion spicifier)]
for example: %05.2f if a float number is 12.5, there will print _12.50(_represent space)
# if you want to print prefix 0 in octal or prefix 0x in hexadecimal(default is not print)
% if you want to print % for example, you can use %% to case it.

2. malloc and calloc
malloc allocate memory but not initialize
void *calloc(size_t nmemb, size_t size) will initialize the memory allocated

3. two-dimensional pointer memory allocate link to priority queue initial.

Author: Shouhua Peng
Date: 29/1/2015
Address: HuBei Provincial Library
*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define ROW 3
#define COLUMN 4

int i,j;

void print(int **p)
{
    for(i=0; i<ROW; i++)
    {
        for(j=0; j<COLUMN; j++)
        {
            printf("%p   ", &p[i][j]);    
        }
        printf("\n");
    }
    printf("\n");
}
int main()
{
    int **p = NULL;
    //int i, j;
    /*Allcote discontinuous memory cell*/
    if((p = (int **)malloc(ROW * sizeof(int *))) == NULL)
    {
        exit(EXIT_FAILURE);    
    }
    for(i=0; i<ROW; i++)
    {
        if((p[i] = (int *)malloc(COLUMN * sizeof(int))) == NULL)
        {
            exit(EXIT_FAILURE);    
        }
    }

    print(p);

    for(i=0; i<ROW; i++)
    {
        free(p[i]);
        p[i] = NULL;
    }
    free(p);
    p = NULL;

    /*Allocate continuous memory cell*/
    int **q = NULL;
    q = (int **)malloc(ROW * sizeof(int *));
    if((q[0] = (int *)calloc(ROW, COLUMN * sizeof(int))) == NULL)
    {
        fprintf(stderr, "q allocate memory failed.\n");
        exit(EXIT_FAILURE);
    }
    for(i=1; i<ROW; i++)
    {
        q[i] = q[i-1] + COLUMN; 
    }
    
    print(q);

    free(q[0]);
    q[0] = NULL;
    free(q);
    q = NULL;

    exit(0);    
}
