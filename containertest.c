/*
this file is aim to test the macro LIST_ENTRY which is often used in linux kernel.
Author: Shouhua Peng
Date: 1/12/2014
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define LIST_ENTRY(ptr, type, member) \
((type *)((char *)(ptr)-(size_t)(&(((type *)0)->member))))

typedef struct node
{
    int data;
    struct node *next;
}Node;

int main(void)
{
    Node n = {1, NULL};
    Node m = {2, NULL};
    n.next = &m;
    Node *pn = LIST_ENTRY(&n.next, Node, next);
    printf("pn's data is: %d\n", pn->data);
    printf("&n:%3x\n&m:%0x\npn:%0x\n", &n, &m, pn);
    exit(0);
}
