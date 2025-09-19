#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char* input) {
    size_t len = strlen(input);
    char* escaped = malloc(len * 6 + 1); // Worst-case scenario length
    if (!escaped) return NULL;

    const char* special_chars[] = {'&', '<', '>', '"', '\''};
    const char* html_entities[] = {"&amp;", "&lt;", "&gt;", "&quot;", "&#39;"};

    size_t j = 0;
    for (size_t i = 0; i < len; ++i) {
        int found = 0;
        for (int k = 0; k < 5; ++k) {
            if (input[i] == special_chars[k]) {
                strcpy(escaped + j, html_entities[k]);
                j += strlen(html_entities[k]);
                found = 1;
                break;
            }
        }
        if (!found) {
            escaped[j++] = input[i];
        }
    }
    escaped[j] = '\0';
    return escaped;
}

char* hello(const char* username) {
    size_t len = strlen(username);
    char* buffer = malloc(len + 16); // "Hello, " + null terminator
    if (!buffer) return NULL;

    snprintf(buffer, len + 16, "Hello, %s", username);
    return buffer;
}

void handle_request(const char* url) {
    const char* path = url + strlen("http://localhost/");
    char* token = strtok((char*)path, "/");
    
    if (strcmp(token, "hello") == 0) {
        token = strtok(NULL, "/");
        if (token != NULL) {
            char* response = hello(escape(token));
            printf("%s\n", response);
            free(response);
        }
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    handle_request("http://localhost/hello/username<>");
    return 0;
}