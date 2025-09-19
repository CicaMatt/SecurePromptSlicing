#include <stdio.h>
#include <string.h>

void escape(const char *input, char *output) {
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
    static char result[256];
    snprintf(result, sizeof(result), "Hello %s", username);
    return result;
}

void handle_request(const char *url) {
    if (strncmp(url, "/hello/", 7) == 0) {
        const char *username = url + 7;
        char safe_username[128];

        escape(username, safe_username);

        printf("%s\n", hello(safe_username));
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    handle_request("/hello/John Doe");
    return 0;
}