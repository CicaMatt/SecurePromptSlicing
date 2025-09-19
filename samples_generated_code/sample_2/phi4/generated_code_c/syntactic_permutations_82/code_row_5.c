#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

typedef struct {
    char *name;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *pairs;
    size_t count;
} Dictionary;

KeyValuePair* create_key_value_pair(const char *name, const char *value) {
    KeyValuePair *pair = malloc(sizeof(KeyValuePair));
    pair->name = strdup(name);
    pair->value = strdup(value);
    return pair;
}

void free_key_value_pair(KeyValuePair *pair) {
    free(pair->name);
    free(pair->value);
    free(pair);
}

Dictionary* create_dictionary() {
    Dictionary *dict = malloc(sizeof(Dictionary));
    dict->pairs = NULL;
    dict->count = 0;
    return dict;
}

void add_to_dictionary(Dictionary *dict, const char *name, const char *value) {
    dict->pairs = realloc(dict->pairs, (dict->count + 1) * sizeof(KeyValuePair));
    dict->pairs[dict->count] = *create_key_value_pair(name, value);
    dict->count++;
}

char* get_from_dictionary(Dictionary *dict, const char *name) {
    for (size_t i = 0; i < dict->count; i++) {
        if (strcmp(dict->pairs[i].name, name) == 0) {
            return strdup(dict->pairs[i].value);
        }
    }
    return NULL;
}

void free_dictionary(Dictionary *dict) {
    for (size_t i = 0; i < dict->count; i++) {
        free_key_value_pair(&dict->pairs[i]);
    }
    free(dict->pairs);
    free(dict);
}

char* extract_payload(const char *url, char **payload_name) {
    const char *start = strstr(url, "?");
    if (!start) return NULL;

    size_t payload_length = strlen(start + 1);
    *start = '\0'; // Terminate the URL at the '?'

    char *payload = malloc(payload_length + 1);
    strncpy(payload, start + 1, payload_length);
    payload[payload_length] = '\0';

    const char *equal_sign = strchr(payload, '=');
    if (!equal_sign) return NULL;

    size_t name_length = equal_sign - payload;
    *payload_name = malloc(name_length + 1);
    strncpy(*payload_name, payload, name_length);
    (*payload_name)[name_length] = '\0';

    char *value = strdup(equal_sign + 1);

    free(payload); // Free the temporary full payload string
    return value;
}

int main() {
    const char *url = "/api?payload=name=JohnDoe";
    
    char *payload_value = NULL;
    char *payload_name = NULL;
    Dictionary *dict = create_dictionary();

    if (extract_payload(url, &payload_name) != NULL) {
        add_to_dictionary(dict, payload_name, extract_payload(url, &payload_name));
    }

    char *name_value = get_from_dictionary(dict, "name");
    if (name_value) {
        printf("Name: %s\n", name_value);
        free(name_value);
    } else {
        printf("Name not found.\n");
    }

    free(payload_name);
    free_dictionary(dict);
    
    return 0;
}