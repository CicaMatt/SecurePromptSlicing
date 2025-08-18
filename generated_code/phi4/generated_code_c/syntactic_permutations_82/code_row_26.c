#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    size_t count;
    KeyValuePair *items;
} Dictionary;

Dictionary* create_dictionary() {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    dict->count = 0;
    dict->items = NULL;
    return dict;
}

void add_to_dictionary(Dictionary *dict, const char *key, const char *value) {
    size_t new_count = dict->count + 1;
    dict->items = (KeyValuePair *)realloc(dict->items, new_count * sizeof(KeyValuePair));
    dict->items[dict->count].key = strdup(key);
    dict->items[dict->count].value = strdup(value);
    dict->count++;
}

char* get_from_dictionary(Dictionary *dict, const char *key) {
    for (size_t i = 0; i < dict->count; ++i) {
        if (strcmp(dict->items[i].key, key) == 0) {
            return dict->items[i].value;
        }
    }
    return NULL;
}

void free_dictionary(Dictionary *dict) {
    for (size_t i = 0; i < dict->count; ++i) {
        free(dict->items[i].key);
        free(dict->items[i].value);
    }
    free(dict->items);
    free(dict);
}

const char* process_request(const char *request_path, const char *payload) {
    if (strncmp(request_path, "/api?", 5) == 0) {
        Dictionary *dict = create_dictionary();
        
        // Extract payload from URL
        char query_string[MAX_PAYLOAD_SIZE];
        strncpy(query_string, request_path + 5, MAX_PAYLOAD_SIZE);
        query_string[strcspn(query_string, "?")] = '\0'; // Remove trailing '?'

        // Split into key-value pairs and load them into the dictionary
        char *pair = strtok(query_string, "&");
        while (pair) {
            char *key_value = strdup(pair);
            char *equal_sign = strchr(key_value, '=');
            if (equal_sign) {
                *equal_sign = '\0';
                add_to_dictionary(dict, key_value, equal_sign + 1);
            }
            free(key_value);
            pair = strtok(NULL, "&");
        }

        // Assume we return the value of a specific parameter "response"
        const char* response = get_from_dictionary(dict, "response");

        // Free resources
        free_dictionary(dict);

        return response ? response : "No response parameter found";
    }
    return "Invalid request path";
}

int main() {
    const char *request_path = "/api?param1=value1&response=HelloWorld";
    
    const char *result = process_request(request_path, NULL);
    printf("Result: %s\n", result);

    return 0;
}