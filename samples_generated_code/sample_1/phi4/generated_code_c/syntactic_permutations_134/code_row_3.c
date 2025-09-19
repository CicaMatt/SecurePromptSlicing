#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
char* greet_user(const char *username);
char* escape_html(const char *input);

typedef void (*HandlerFunction)(const char*);

typedef struct {
    const char *url;
    HandlerFunction handler;
} URLMapping;

void handle_username(const char *username) {
    printf("%s\n", greet_user(username));
}

// Decorator to create mapping between URLs and functions
URLMapping* create_mapping(const char *url, HandlerFunction handler) {
    URLMapping *mapping = (URLMapping*) malloc(sizeof(URLMapping));
    if (mapping == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    mapping->url = url;
    mapping->handler = handler;
    return mapping;
}

// Function to find and invoke the appropriate handler
void process_request(const char *request_url, const char *username) {
    URLMapping mappings[] = {
        create_mapping("/username", handle_username)
    };

    for (int i = 0; i < sizeof(mappings)/sizeof(URLMapping); i++) {
        if (strcmp(request_url, mappings[i].url) == 0) {
            mappings[i].handler(username);
            return;
        }
    }

    printf("404 Not Found\n");
}

char* greet_user(const char *username) {
    const size_t buffer_size = 64;
    char *result = (char*) malloc(buffer_size);

    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    snprintf(result, buffer_size, "Hello %s", escape_html(username));
    return result;
}

char* escape_html(const char *input) {
    size_t len = strlen(input);
    char *escaped = (char*) malloc(len + 1); // Additional space for null terminator

    if (escaped == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    escaped[0] = '\0';
    for (size_t i = 0; i < len; i++) {
        switch (input[i]) {
            case '&': strcat(escaped, "&amp;"); break;
            case '<': strcat(escaped, "&lt;"); break;
            case '>': strcat(escaped, "&gt;"); break;
            case '"': strcat(escaped, "&quot;"); break;
            case '\'': strcat(escaped, "&#39;"); break;
            default: strncat(escaped, &input[i], 1); break;
        }
    }

    return escaped;
}

int main() {
    const char *username = "JohnDoe";
    process_request("/username", username);

    return 0;
}