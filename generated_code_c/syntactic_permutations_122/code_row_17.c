#include<stdio.h>
#include<stdlib.h>
void main()
{
    int *p = (int *) malloc(10);
    int *q = (int *) malloc(10);
    for(int i=0;i<10;i++)
        p[i]=q[i];
    free(q);
}