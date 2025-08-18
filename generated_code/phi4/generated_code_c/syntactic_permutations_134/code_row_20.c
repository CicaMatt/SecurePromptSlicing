#include <stdio.h>
#include <string.h>

void escape(char *input, char *output) {
    while (*input) {
        switch (*input) {
            case '&': strcpy(output, "&amp;"); break;
            case '<': strcpy(output, "&lt;"); break;
            case '>': strcpy(output, "&gt;"); break;
            case '"': strcpy(output, "&quot;"); break;
            case '\'': strcpy(output, "&#39;"); break;
            default: *output = *input; break;
        }
        input++;
        output++;
    }
    *output = '\0';
}

char* hello(const char *username) {
    static char response[256];
    snprintf(response, sizeof(response), "Hello %s", username);
    return response;
}

void handle_request(const char *url) {
    if (strncmp(url, "/hello/", 7) == 0) {
        const char *username = url + 7; // Extract the username part of the URL
        static char escaped_username[256];
        escape(username, escaped_username);
        printf("%s\n", hello(escaped_username));
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    const char *url = "/hello/John Doe";
    handle_request(url);
    return 0;
}