#include <stdio.h>
#include <stdlib.h>
int main(){
    char *buf;
    buf = (char *)malloc(sizeof(char)*1024);
    gets(buf);
    
    char *buf1;
    buf1 = (char *)malloc(sizeof(char)*1024);
    gets(buf1);
}