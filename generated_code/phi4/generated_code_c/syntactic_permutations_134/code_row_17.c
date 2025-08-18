#include <stdio.h>
#include <string.h>

void escape(const char *input, char *output) {
    const char *special_chars = "&<>'\"";
    while (*input) {
        if (strchr(special_chars, *input)) {
            switch (*input) {
                case '&': strcat(output, "&amp;"); break;
                case '<': strcat(output, "&lt;"); break;
                case '>': strcat(output, "&gt;"); break;
                case '\'': strcat(output, "&#39;"); break;
                case '\"': strcat(output, "&quot;"); break;
            }
        } else {
            strncat(output, input, 1);
        }
        input++;
    }
}

char* hello(const char *username) {
    static char result[256];
    char escaped_username[256] = "";

    escape(username, escaped_username);

    snprintf(result, sizeof(result), "Hello %s", escaped_username);
    return result;
}

void handle_request(const char *url) {
    const char *prefix = "/hello/";
    if (strncmp(url, prefix, strlen(prefix)) == 0) {
        const char *username = url + strlen(prefix);
        printf("%s\n", hello(username));
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    handle_request("/hello/John Doe");
    handle_request("/hello/<script>alert('hi');</script>");
    handle_request("/notfound");
    return 0;
}