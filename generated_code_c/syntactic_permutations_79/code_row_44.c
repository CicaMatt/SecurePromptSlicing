#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *buf,*buf1;
    size_t n = 1024;
    buf = malloc(n);
    fgets(buf,n,stdin);
    
    printf("Enter another string: ");

    buf1 = malloc(n);
    fgets(buf1,n,stdin);

}