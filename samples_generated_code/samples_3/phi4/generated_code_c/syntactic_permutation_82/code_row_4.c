#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

// Function to extract key-value pairs from query string
void parse_query_string(const char *query, char **name_value) {
    const char *delimiter = "&";
    char *token = strtok((char *)query, delimiter);
    
    while (token != NULL) {
        char *key_value = malloc(BUFFER_SIZE);
        if (strchr(token, '=') != NULL) {
            strcpy(key_value, token);
            *name_value = key_value;
        }
        token = strtok(NULL, delimiter);
    }
}

// Function to extract the value for a given key
char* get_value_from_dict(const char *dict, const char *key) {
    char *start = strstr(dict, key);
    if (start == NULL) {
        return NULL;
    }

    start += strlen(key); // Move pointer to '=' character
    if (*start != '=') {
        return NULL; // Key not found or malformed
    }
    
    start++; // Move past '='
    char *end = strchr(start, '&');
    if (end == NULL) {
        end = strpbrk(start, "\r\n"); // Handle end of string
    }

    int length = end ? (int)(end - start) : strlen(start);
    char *value = malloc(length + 1);
    strncpy(value, start, length);
    value[length] = '\0';

    return value;
}

// Simulate handling a request to the /api endpoint
void handle_api_request(const char *url) {
    const char *path_start = strstr(url, "/api?");
    if (path_start == NULL) {
        printf("Invalid API path\n");
        return;
    }

    // Extract query string
    path_start += 5; // Skip "/api?"
    char *name_value = malloc(BUFFER_SIZE);
    parse_query_string(path_start, &name_value);

    // Get the value for 'name' key from query string
    char *result = get_value_from_dict(name_value, "name");
    if (result != NULL) {
        printf("Name: %s\n", result);
        free(result);
    } else {
        printf("Name parameter not found or invalid.\n");
    }

    free(name_value);
}

int main() {
    const char *url = "http://example.com/api?name=JohnDoe&age=30";
    handle_api_request(url);

    return 0;
}