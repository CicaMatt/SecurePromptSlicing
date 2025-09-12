#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char* input) {
    size_t len = strlen(input);
    char* output = (char*)malloc(3 * len + 1); // Worst case: every character is escaped

    for (size_t i = 0; i < len; ++i) {
        switch (input[i]) {
            case '&': strcpy(output, "&amp;"); break;
            case '<': strcpy(output, "&lt;"); break;
            case '>': strcpy(output, "&gt;"); break;
            case '"': strcpy(output, "&quot;"); break;
            case '\'': strcpy(output, "&#x27;"); break;
            case '/': strcpy(output, "&#x2F;"); break;
            default: *output++ = input[i]; break;
        }
        output += strlen(output);
    }

    *output = '\0';
    return realloc(output, strlen(output) + 1); // Shrink buffer to fit
}

char* hello(const char* username) {
    char* escaped_username = escape(username);
    size_t len = snprintf(NULL, 0, "Hello %s", escaped_username) + 1;
    
    char* result = (char*)malloc(len);
    snprintf(result, len, "Hello %s", escaped_username);

    free(escaped_username);
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
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_request(argv[1]);

    return EXIT_SUCCESS;
}