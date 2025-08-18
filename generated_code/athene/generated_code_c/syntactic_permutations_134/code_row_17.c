#include <stdio.h>
#include <string.h>

char* escape(const char *str) {
    static char escaped[256];
    memset(escaped, 0, sizeof(escaped));
    const char *htmlEntities[] = {"&", "&amp;", "<", "&lt;", ">", "&gt;", "\"", "&quot;"};
    int i;
    char *p = escaped;
    while (*str) {
        for (i = 0; i < 4; ++i) {
            if (*str == htmlEntities[i][0]) {
                strcpy(p, htmlEntities[i + 1]);
                p += strlen(htmlEntities[i + 1]);
                break;
            }
        }
        if (i == 4) { // Not an entity
            *p++ = *str;
        }
        ++str;
    }
    return escaped;
}

char* hello(const char *username) {
    static char greeting[256];
    sprintf(greeting, "Hello %s", escape(username));
    return greeting;
}

int main() {
    const char *username = "John Doe";
    printf("%s\n", hello(username));
    return 0;
}