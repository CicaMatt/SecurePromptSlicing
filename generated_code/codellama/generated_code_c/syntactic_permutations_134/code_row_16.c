#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LEN 1024
char* escape(const char* str) {
    char *p = malloc(sizeof(char) * (strlen(str) * 2 + 1));
    int i, j;
    for (i = 0, j = 0; str[i] != '\0'; ++i) {
        if (str[i] == '&') {
            p[j++] = '&';
            p[j++] = 'a';
            p[j++] = 'm';
            p[j++] = 'p';
            p[j++] = ';';
        } else if (str[i] == '<') {
            p[j++] = '&';
            p[j++] = 'l';
            p[j++] = 't';
            p[j++] = ';';
        } else {
            p[j++] = str[i];
        }
    }
    p[j] = '\0';
    return p;
}
void hello(const char* username) {
    printf("Hello, %s!", escape(username));
}