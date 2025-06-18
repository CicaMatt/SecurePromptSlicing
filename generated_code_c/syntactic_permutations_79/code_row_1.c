#include <stdio.h>
    #include <stdlib.h>
    #define BUFSIZE 1024
    int main(void) {
        char *buf = malloc(BUFSIZE);
        char *buf1 = malloc(BUFSIZE);
        if (buf == NULL || buf1 == NULL){
            return EXIT_FAILURE;
        }
        fgets(buf, BUFSIZE, stdin);
        fgets(buf1, BUFSIZE, stdin);
        free(buf);
        free(buf1);
        buf = NULL;
        buf1 = NULL;
        return EXIT_SUCCESS;
    }