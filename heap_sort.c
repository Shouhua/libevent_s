/*

this program is mainly to get or delete the max element in a array, which is refered to wikipedia.org.
and this is not sort the whole array and just get or delete the max/min elements in array.
first of all, we should clear about how to get parent and left/right child element:
    left(i) = (2*i)+1 (i is parent element index)
    right(i) = (2*i)+2(i is parent element index)
    parent(i) = floor((i-1)/2)
1) when we insert element, we set the last element is our target, and compare the element and its parent
    recursively.

2) when we delete/get the heap top, 

Author: Shouhua Peng
Date:1/12/2014
*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_HEAP_LEN 10
static int heap[MAX_HEAP_LEN];
static int heap_size;

static void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static void shift_up(int i)
{
    int done = 0;
    if(i == 0) return;
    while(i !=0 && !done)
    {
        if(heap[i] > heap[(i-1)/2])
            swap(&heap[i], &heap[(i-1)/2]);
        else
            done = 1;
        i = (i-1)/2;
    }
}

static void shift_down(int i)
{
    int done = 0;
    if(2*i+1 > heap_size) return;
    while((2*i+1 < heap_size) && (!done))
    {
        i = 2*i + 1;
        if((i+1 < heap_size) && (heap[i+1] > heap[i]))
            i++;
        if(heap[(i-1)/2] < heap[i])
            swap(&heap[(i-1)/2], &heap[i]);
        else
            done = 1;
    }
}

static void delete(int i)
{
    int last = heap[heap_size - 1];
    heap_size--;
    if(i == heap_size) return;
    heap[i] = last;
    shift_down(i);
}

int delete_max()
{
    int ret = heap[0];
    delete(0);
    return ret;
}

void insert(int new_data)
{
    if(heap_size >= MAX_HEAP_LEN) return;
    heap_size++;
    heap[heap_size-1] = new_data;
    shift_up(heap_size-1);
}

static void print(int heap[], int size)
{
    int i;
    for(i=0;i<size;i++)
        printf("%d ", heap[i]);
    printf("\n");
}

int main()
{
    int i, data;
    for(i=0;i<10;i++)
    {
        data = rand()%100;
        printf("%d ", data);
        insert(data);    
    }
    printf("\n");
    print(heap, MAX_HEAP_LEN);
    printf("after delete max one:\n");
    int max = delete_max();
    printf("the max one is: %d\n", max);
    print(heap, MAX_HEAP_LEN-1);
    exit(0);    
}
