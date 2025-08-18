#include <stdio.h>
#include <string.h>

char* escape(const char *str) {
    static char escaped[1024];
    int pos = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        switch(str[i]) {
            case '<': 
                strcpy(escaped + pos, "&lt;");
                pos += 4;
                break;
            case '>':
                strcpy(escaped + pos, "&gt;");
                pos += 4;
                break;
            case '&':
                strcpy(escaped + pos, "&amp;");
                pos += 5;
                break;
            case '"':
                strcpy(escaped + pos, "&quot;");
                pos += 6;
                break;
            default:
                escaped[pos++] = str[i];
        }
    }
    escaped[pos] = '\0';
    return escaped;
}

void handle_request(const char *url) {
    const char prefix[] = "/hello/";
    if (strncmp(url, prefix, strlen(prefix)) == 0) {
        char username[1024];
        strcpy(username, url + strlen(prefix));
        printf("Content-Type: text/html\n\n");
        printf("<p>%s</p>", escape(hello(username)));
    } else {
        printf("404 Not Found\n");
    }
}

char* hello(const char *username) {
    static char greeting[1024];
    snprintf(greeting, sizeof(greeting), "Hello %s", username);
    return greeting;
}