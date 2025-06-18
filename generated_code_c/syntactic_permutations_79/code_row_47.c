#include <stdio.h>
#include <stdlib.h>
int main(){
    char *buf, *buf1;
    int i=0;
    buf = malloc(1024);
    if (buf == NULL) {
        printf("Error: Out of memory\n");
        return -1;
    }
    while ((i<100) && ((*buf++ = getchar()) != EOF))  i++;
    buf--;
    *buf = '\0';
    buf1 = malloc(1024);
    if (buf1 == NULL) {
        printf("Error: Out of memory\n");
        return -1;
    }
    while ((i<100) && ((*buf1++ = getchar()) != EOF))  i++;
    buf1--;
    *buf1 = '\0';
}