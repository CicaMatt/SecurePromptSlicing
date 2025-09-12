#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void escape(char *input, char *output) {
    const char *special_chars = "&<>'\"";
    while (*input) {
        if (strchr(special_chars, *input)) {
            switch (*input) {
                case '&': strcpy(output, "&amp;"); break;
                case '<': strcpy(output, "&lt;"); break;
                case '>': strcpy(output, "&gt;"); break;
                case '\'': strcpy(output, "&#39;"); break;
                case '"': strcpy(output, "&quot;"); break;
            }
            input++;
            output += strlen(output);
        } else {
            *output++ = *input++;
        }
    }
    *output = '\0';
}

char* hello(const char* username) {
    static char buffer[256];
    char escaped_username[128];

    escape(username, escaped_username);

    snprintf(buffer, sizeof(buffer), "Hello %s", escaped_username);
    return buffer;
}

void handle_request(const char* url) {
    if (strncmp(url, "/hello/", 7) == 0) {
        const char *username = url + 7;
        printf("%s\n", hello(username));
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    // Simulate user navigating to a URL
    handle_request("/hello/John Doe<script>alert('XSS')</script>");
    return 0;
}