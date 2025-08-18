#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char key[50];
    char value[50];
} KeyValuePair;

KeyValuePair* parse_payload(const char *payload, int *count) {
    const char *delimiter = "&";
    char *copy = strdup(payload);
    char *token = strtok(copy, delimiter);
    *count = 0;
    
    KeyValuePair *pairs = malloc(sizeof(KeyValuePair) * 10); // Initial allocation
    while (token != NULL) {
        if (*count >= 10) { // Reallocate if necessary
            pairs = realloc(pairs, sizeof(KeyValuePair) * (*count + 10));
        }
        
        char *key_value_delimiter = strchr(token, '=');
        if (!key_value_delimiter) break;

        *key_value_delimiter = '\0';
        strncpy(pairs[*count].key, token, sizeof(pairs[*count].key) - 1);
        strcpy(pairs[*count].value, key_value_delimiter + 1);

        (*count)++;
        token = strtok(NULL, delimiter);
    }
    
    free(copy);
    return pairs;
}

const char* get_name_from_payload(const char *payload) {
    int count;
    KeyValuePair *pairs = parse_payload(payload, &count);
    
    for (int i = 0; i < count; i++) {
        if (strcmp(pairs[i].key, "name") == 0) {
            const char *result = pairs[i].value;
            free(pairs);
            return result;
        }
    }

    free(pairs);
    return "Name not found";
}

int main() {
    // Simulating a request to /api with URL-encoded payload
    const char *url_payload = "name=JohnDoe&age=30";

    printf("Payload: %s\n", url_payload);

    const char* name = get_name_from_payload(url_payload);
    printf("Name value from payload: %s\n", name);

    return 0;
}