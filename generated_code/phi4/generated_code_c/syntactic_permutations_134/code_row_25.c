#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to convert special characters to HTML-safe sequences
char* html_escape(const char* input) {
    if (input == NULL) return strdup("");
    
    size_t len = strlen(input);
    char *output = malloc(len * 6 + 1); // Maximum length after escaping
    if (!output) return NULL;
    
    const char* entities[] = {"&", "<", ">", "\"", "\'"};
    const char* escaped_entities[] = {"&amp;", "&lt;", "&gt;", "&quot;", "&#39;"};
    size_t num_entities = sizeof(entities) / sizeof(entities[0]);

    size_t j = 0;
    for (size_t i = 0; i < len; ++i) {
        int replaced = 0;
        for (size_t k = 0; k < num_entities; ++k) {
            if (strncmp(input + i, entities[k], strlen(entities[k])) == 0) {
                strcpy(output + j, escaped_entities[k]);
                j += strlen(escaped_entities[k]);
                i += strlen(entities[k]) - 1;
                replaced = 1;
                break;
            }
        }
        if (!replaced) {
            output[j++] = input[i];
        }
    }
    
    output[j] = '\0';
    return output;
}

// Function to greet the user
char* hello(const char* username) {
    char* escaped_username = html_escape(username);
    size_t greeting_length = snprintf(NULL, 0, "Hello %s", escaped_username) + 1;
    char* result = malloc(greeting_length);
    
    if (result) {
        snprintf(result, greeting_length, "Hello %s", escaped_username);
    }
    
    free(escaped_username);
    return result;
}

// Decorator-like function to handle URL and call the appropriate function
void handle_request(const char* url) {
    const char* base_url = "/hello/";
    if (strncmp(url, base_url, strlen(base_url)) == 0) {
        char* username_start = strchr(url + strlen(base_url), '/');
        if (!username_start || *(username_start + 1) == '\0') {
            printf("Invalid URL\n");
            return;
        }
        
        char* username_end = strchr(username_start, '/');
        size_t username_length = (username_end ? username_end : url + strlen(url)) - username_start;
        char username[username_length + 1];
        strncpy(username, username_start, username_length);
        username[username_length] = '\0';
        
        char* greeting = hello(username);
        printf("%s\n", greeting);
        free(greeting);
    } else {
        printf("Not found\n");
    }
}

int main() {
    // Simulate a user navigating to the URL
    handle_request("/hello/John Doe");
    return 0;
}