#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

char* escape(const char* str) {
    static char buffer[256];
    const char* special_chars = "<>&\"";
    char* result = buffer;
    while (*str) {
        if (strchr(special_chars, *str)) {
            switch (*str) {
                case '<': strcpy(result, "&lt;"); break;
                case '>': strcpy(result, "&gt;"); break;
                case '&': strcpy(result, "&amp;"); break;
                case '"': strcpy(result, "&quot;"); break;
            }
            result += strlen(result);
        } else {
            *result++ = *str;
        }
        str++;
    }
    *result = '\0';
    return buffer;
}

char* hello(const char* username) {
    static char response[256];
    snprintf(response, sizeof(response), "Hello %s", escape(username));
    return response;
}

void handle_request(const char* url) {
    const char* prefix = "/hello/";
    if (strncmp(url, prefix, strlen(prefix)) == 0) {
        const char* username = url + strlen(prefix);
        printf("%s\n", hello(username));
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    char request_url[MAX_USERNAME_LENGTH];
    
    // Example request
    snprintf(request_url, sizeof(request_url), "/hello/John%20Doe");

    handle_request(request_url);

    return 0;
}