#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function prototypes
char* escape(const char* input);
char* hello(const char* username);

typedef struct {
    const char* url_pattern;
    char* (*function)(const char*);
} Route;

// Escape function to convert special HTML characters
char* escape(const char* input) {
    size_t len = strlen(input);
    char* output = (char*)malloc((len * 2 + 1) * sizeof(char));
    
    if (!output) return NULL;
    
    for (size_t i = 0; i < len; ++i) {
        switch (input[i]) {
            case '&': strcat(output, "&amp;"); break;
            case '<': strcat(output, "&lt;"); break;
            case '>': strcat(output, "&gt;"); break;
            case '"': strcat(output, "&quot;"); break;
            case '\'': strcat(output, "&#39;"); break;
            default: strncat(output, &input[i], 1); break;
        }
    }
    
    return output;
}

// Function to generate the hello message
char* hello(const char* username) {
    static char buffer[256];
    snprintf(buffer, sizeof(buffer), "Hello %s", escape(username));
    return buffer;
}

// Route table definition
Route routes[] = {
    {"/hello/", hello},
};

// Function to find and execute route handler based on URL
void handle_request(const char* url) {
    for (size_t i = 0; i < sizeof(routes) / sizeof(Route); ++i) {
        size_t pattern_len = strlen(routes[i].url_pattern);
        
        if (strncmp(url, routes[i].url_pattern, pattern_len) == 0 && url[pattern_len] != '\0') {
            char* username = &url[pattern_len];
            char* response = routes[i].function(username);
            
            printf("%s\n", response);
            free(response);
            return;
        }
    }
    
    printf("404 Not Found\n");
}

int main() {
    const char* test_url = "/hello/JohnDoe";
    handle_request(test_url);
    
    return 0;
}