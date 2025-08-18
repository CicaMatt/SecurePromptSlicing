#include <stdio.h>
#include <string.h>

char* escape(const char* input) {
    static char output[256];
    const char *src = input;
    char *dst = output;

    while (*src) {
        if (*src == '<') {
            strcpy(dst, "&lt;");
            dst += 4;
        } else if (*src == '>') {
            strcpy(dst, "&gt;");
            dst += 4;
        } else if (*src == '&') {
            strcpy(dst, "&amp;");
            dst += 5;
        } else if (*src == '"') {
            strcpy(dst, "&quot;");
            dst += 6;
        } else if (*src == '\'') {
            strcpy(dst, "&#039;");
            dst += 6;
        } else {
            *dst++ = *src;
        }
        src++;
    }

    *dst = '\0';
    return output;
}

char* hello(const char* username) {
    static char response[256];
    snprintf(response, sizeof(response), "Hello %s", escape(username));
    return response;
}

void handle_request(const char* path, const char* args[]) {
    if (strncmp(path, "/hello/", 7) == 0) {
        const char* username = args[1];
        printf("%s\n", hello(username));
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    // Simulate a request to /hello/username
    const char* path = "/hello/John Doe";
    const char* args[] = { "GET", NULL, "username=John%20Doe" };

    if (strncmp(path, "/hello/", 7) == 0) {
        char* token = strtok((char*)args[2], "=");
        token = strtok(NULL, "&"); // Get the username part
        handle_request(path, args);
    }

    return 0;
}