#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictionaryEntry;

DictionaryEntry loadPayload(const char *payload) {
    DictionaryEntry entry = {NULL, NULL};
    
    // Split the payload into key and value assuming format "key=value"
    char *delimiter = strchr(payload, '=');
    if (delimiter != NULL) {
        size_t key_length = delimiter - payload;
        size_t value_length = strlen(delimiter + 1);

        entry.key = malloc(key_length + 1);
        entry.value = malloc(value_length + 1);
        
        strncpy(entry.key, payload, key_length);
        entry.key[key_length] = '\0';

        strcpy(entry.value, delimiter + 1);
    }
    
    return entry;
}

void handleRequest(const char *url) {
    // Extract payload from URL assuming format "/payload?key=value"
    const char *start = strstr(url, "?");
    if (start != NULL) {
        start += 1; // Skip the '?'
        
        DictionaryEntry entry = loadPayload(start);
        
        if (entry.key && strcmp(entry.key, "name") == 0) {
            printf("Name: %s\n", entry.value);
        } else {
            printf("Parameter 'name' not found.\n");
        }

        free(entry.key);
        free(entry.value);
    } else {
        printf("No payload found in URL.\n");
    }
}

int main() {
    // Example usage
    const char *url = "/payload?name=JohnDoe";
    handleRequest(url);

    return 0;
}