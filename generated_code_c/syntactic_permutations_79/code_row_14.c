#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    char *buf,*buf1;
    buf = (char*)malloc(1024);
    fgets(buf,1024,stdin); 
    printf("%s",buf);
    free(buf);
    return 0;
}