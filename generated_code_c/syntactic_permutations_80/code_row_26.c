#include<stdio.h>
void scan(char str[],int n)
{
    printf("scanf(%s,%d)",str,n);
}
int main()
{
    char str[1024];
    scan(str,1023);
    return 0;
}