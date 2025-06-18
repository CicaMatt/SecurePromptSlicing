#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 1024;
int main() {
    char *buf = (char *) malloc(BUFFER_SIZE);
    if (buf == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    fgets(buf, BUFFER_SIZE, stdin);
    
    char *buf1 = (char *) malloc(BUFFER_SIZE);
    if (buf1 == NULL) {
        printf("Memory allocation error\n");
        exit(2);
    }
    fgets(buf1, BUFFER_SIZE, stdin);
    
    free(buf);
    free(buf1);
}