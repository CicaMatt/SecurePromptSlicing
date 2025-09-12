#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char* str) {
    int len = strlen(str);
    char* escaped_str = malloc(2 * len + 1);
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] == '&') {
            strcpy(&escaped_str[j], "&amp;");
            j += 5;
        } else if (str[i] == '<') {
            strcpy(&escaped_str[j], "&lt;");
            j += 4;
        } else if (str[i] == '>') {
            strcpy(&escaped_str[j], "&gt;");
            j += 4;
        } else if (str[i] == '"') {
            strcpy(&escaped_str[j], "&quot;");
            j += 6;
        } else if (str[i] == '\'') {
            strcpy(&escaped_str[j], "&#39;");
            j += 5;
        } else {
            escaped_str[j++] = str[i];
        }
    }
    escaped_str[j] = '\0';
    return escaped_str;
}

char* hello(const char* username) {
    char* safe_username = escape(username);
    char* result = malloc(strlen(safe_username) + 7);
    sprintf(result, "Hello %s", safe_username);
    free(safe_username);
    return result;
}

void handle_request(const char* url) {
    if (strncmp(url, "/hello/", 7) == 0) {
        const char* username = url + 7;
        char* response = hello(username);
        printf("%s\n", response);
        free(response);
    } else {
        printf("404 Not Found\n");
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <URL>\n", argv[0]);
        return 1;
    }
    handle_request(argv[1]);
    return 0;
}