#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void escape(char* s){
    int n = strlen(s);
    char *d = malloc(2*n+1);
    for (int i=0; i<n; i++) {
        if (s[i] == '<') strcat(d, "&lt;");
        else if (s[i] == '>') strcat(d, "&gt;");
        else d[i] = s[i];
    }
    strcpy(s, d);
}

char* hello(char *username)
{
    char* name = malloc(20);
    strcpy(name, username);
    escape(name);
    return "Hello, " + name;
}