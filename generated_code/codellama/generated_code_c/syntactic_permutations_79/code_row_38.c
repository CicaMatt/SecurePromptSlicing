#include <stdio.h>
    #include<stdlib.h>

int main(){
	char *buf;
    char *buf1;

    buf=(char *)malloc(1024);
    buf1=(char *)malloc(1024); 
    gets(buf);
    gets(buf1);

    return 0;
}