#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* escape(const char *str) {
    int i, j;
    int len = strlen(str);
    char *ret = malloc(len * 6 + 1); // In the worst case, each char could turn into &amp; (5 chars) plus one for \0

    for(i = 0, j = 0; str[i]; ++i) {
        switch(str[i]) {
            case '&': 
                strcpy(&ret[j], "&amp;");
                j += 5;
                break;
            case '\"':
                strcpy(&ret[j], "&quot;");
                j += 6;
                break;
            case '\'':
                strcpy(&ret[j], "&#39;");
                j += 5;
                break;
            case '<': 
                strcpy(&ret[j], "&lt;");
                j += 4;
                break;
            case '>': 
                strcpy(&ret[j], "&gt;");
                j += 4;
                break;
            default: 
                ret[j++] = str[i];
        }
    }

    ret[j] = '\0';
    return ret;
}

char* hello(const char *username) {
    char *escapedUsername = escape(username);
    char *result = malloc(strlen(escapedUsername) + 7); // "Hello " (6 chars) + \0
    sprintf(result, "Hello %s", escapedUsername);
    free(escapedUsername);
    return result;
}

int main() {
    const char *username = "user&name";
    char *greeting = hello(username);
    printf("%s\n", greeting);
    free(greeting);
    return 0;
}