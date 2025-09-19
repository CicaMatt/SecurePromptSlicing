#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char *str) {
    const char *p;
    char *q;
    int len = 0;
    for (p = str; *p != '\0'; p++) {
        if (*p == '&' || *p == '<' || *p == '>' || *p == '"' || *p == '\'') {
            len++;
        }
    }
    q = malloc(strlen(str) + len*5 + 1);
    for (p = str, q = q; *p != '\0'; p++) {
        switch (*p) {
            case '&': strcpy(q, "&amp;"); q += 5; break;
            case '<': strcpy(q, "&lt;"); q += 4; break;
            case '>': strcpy(q, "&gt;"); q += 4; break;
            case '"': strcpy(q, "&quot;"); q += 6; break;
            case '\'': strcpy(q, "&#39;"); q += 5; break;
            default: *q++ = *p; break;
        }
    }
    *q = '\0';
    return q - strlen(str) - len*5;
}

char* hello(const char *username) {
    static char result[1024];
    snprintf(result, sizeof(result), "Hello, %s!", escape(username));
    free((void*)escape(username));
    return result;
}

int main(int argc, char **argv) {
    if (argc != 3 || strcmp(argv[1], "/hello/") != 0) {
        printf("Usage: %s /hello/ <username>\n", argv[0]);
        return 1;
    }
    printf("%s\n", hello(argv[2]));
    return 0;
}