#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototype declarations
char* escape(const char* input);
char* hello(const char* username);

// Simple in-memory routing table
typedef struct Route {
    const char* path;
    char* (*handler)(const char*);
} Route;

// Escape function implementation
char* escape(const char* input) {
    if (input == NULL) return strdup("");
    
    size_t len = strlen(input);
    char* escaped = malloc(len * 6 + 1); // Allocate more space for possible escapes
    if (!escaped) return NULL;
    
    const char* entities[] = {"&", "<", ">", "\"", "'", NULL};
    const char* escape_sequences[] = {"&amp;", "&lt;", "&gt;", "&quot;", "&#39;", ""};
    
    escaped[0] = '\0';
    for (size_t i = 0; input[i]; ++i) {
        for (int j = 0; entities[j]; ++j) {
            size_t entity_len = strlen(entities[j]);
            if (strncmp(&input[i], entities[j], entity_len) == 0) {
                strcat(escaped, escape_sequences[j]);
                i += entity_len - 1;
                break;
            }
        }
        char c = input[i];
        if (!strchr("&<>\\""", c)) {
            strncat(escaped, &c, 1);
        } else {
            sprintf(escaped + strlen(escaped), "&#%d;", (unsigned char)c);
        }
    }
    
    return escaped;
}

// Hello function implementation
char* hello(const char* username) {
    if (!username || strlen(username) == 0) {
        return strdup("Hello, guest!");
    }

    size_t buffer_size = snprintf(NULL, 0, "Hello, %s!", escape(username)) + 1;
    char* response = malloc(buffer_size);
    if (response) {
        snprintf(response, buffer_size, "Hello, %s!", escape(username));
    }
    
    return response;
}

// Function to handle routing
char* route_handler(const char* path, const char* url_path) {
    Route routes[] = {
        {"/hello/", hello},
        {NULL, NULL}
    };

    for (int i = 0; routes[i].path != NULL; ++i) {
        if (strncmp(path, url_path, strlen(routes[i].path)) == 0 && 
            (strlen(url_path) == strlen(routes[i].path) || url_path[strlen(routes[i].path)] == '/')) {
            
            const char* username = &url_path[strlen(routes[i].path)];
            return routes[i].handler(username);
        }
    }

    return strdup("404 Not Found");
}

// Main function to simulate handling a URL
int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* url_path = argv[1];
    char* response = route_handler(url_path, url_path);

    printf("%s\n", response);
    free(response);

    return EXIT_SUCCESS;
}