#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *pairs;
    size_t count;
} Dictionary;

Dictionary* create_dictionary() {
    Dictionary *dict = malloc(sizeof(Dictionary));
    dict->pairs = NULL;
    dict->count = 0;
    return dict;
}

void add_to_dictionary(Dictionary *dict, const char *key, const char *value) {
    dict->pairs = realloc(dict->pairs, (dict->count + 1) * sizeof(KeyValuePair));
    dict->pairs[dict->count].key = strdup(key);
    dict->pairs[dict->count].value = strdup(value);
    dict->count++;
}

char* get_value_from_dictionary(Dictionary *dict, const char *key) {
    for (size_t i = 0; i < dict->count; i++) {
        if (strcmp(dict->pairs[i].key, key) == 0) {
            return dict->pairs[i].value;
        }
    }
    return NULL;
}

void free_dictionary(Dictionary *dict) {
    for (size_t i = 0; i < dict->count; i++) {
        free(dict->pairs[i].key);
        free(dict->pairs[i].value);
    }
    free(dict->pairs);
    free(dict);
}

int main() {
    char buffer[BUFFER_SIZE];
    printf("Enter payload (in the format key1=value1&key2=value2...): ");
    fgets(buffer, BUFFER_SIZE, stdin);

    Dictionary *dict = create_dictionary();
    char *token = strtok(buffer, "&");
    while (token != NULL) {
        char *equal_sign = strchr(token, '=');
        if (equal_sign != NULL) {
            *equal_sign = '\0';
            add_to_dictionary(dict, token, equal_sign + 1);
        }
        token = strtok(NULL, "&");
    }

    printf("Enter key to retrieve: ");
    char key[BUFFER_SIZE];
    fgets(key, BUFFER_SIZE, stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline character

    char *value = get_value_from_dictionary(dict, key);
    if (value != NULL) {
        printf("Value for '%s': %s\n", key, value);
    } else {
        printf("Key not found.\n");
    }

    free_dictionary(dict);
    return 0;
}