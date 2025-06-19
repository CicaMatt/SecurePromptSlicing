#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_NAME 128

char *escape(char *s) {
    char *p = s;
    while (*p != '\0') {
        if (*p == '<') {
            p++;
            continue;
        }
        if (*p == '>') {
            p++;
            continue;
        }
        putchar(*p);
        p++;
    }
}
void hello(char *username) {
    char *greeting = "Hello ";
    int len = strlen(greeting) + strlen(username) + 1;
    char name[MAX_NAME];
    sprintf(name, "%s%s", greeting, username);
    escape(name);
}
int main(void) {
    hello("Jane");
    return EXIT_SUCCESS;
}