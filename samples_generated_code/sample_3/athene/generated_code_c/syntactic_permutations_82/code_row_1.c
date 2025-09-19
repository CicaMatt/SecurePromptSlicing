#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    int count;
    KeyValuePair **pairs;
} Dictionary;

Dictionary *create_dictionary() {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    dict->count = 0;
    dict->pairs = NULL;
    return dict;
}

void add_to_dictionary(Dictionary *dict, const char *key, const char *value) {
    KeyValuePair *pair = (KeyValuePair *)malloc(sizeof(KeyValuePair));
    pair->key = strdup(key);
    pair->value = strdup(value);

    dict->count++;
    dict->pairs = (KeyValuePair **)realloc(dict->pairs, dict->count * sizeof(KeyValuePair *));
    dict->pairs[dict->count - 1] = pair;
}

char *get_from_dictionary(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->count; i++) {
        if (strcmp(dict->pairs[i]->key, key) == 0) {
            return dict->pairs[i]->value;
        }
    }
    return NULL;
}

void free_dictionary(Dictionary *dict) {
    for (int i = 0; i < dict->count; i++) {
        free(dict->pairs[i]->key);
        free(dict->pairs[i]->value);
        free(dict->pairs[i]);
    }
    free(dict->pairs);
    free(dict);
}

char *parse_payload(const char *payload) {
    Dictionary *dict = create_dictionary();
    const char *token = strtok((char *)payload, "&");
    while (token != NULL) {
        char *key_value = token;
        char *value = strchr(key_value, '=');
        if (value != NULL) {
            *value++ = '\0';
            add_to_dictionary(dict, key_value, value);
        }
        token = strtok(NULL, "&");
    }

    char *name = get_from_dictionary(dict, "name");
    free_dictionary(dict);
    return name;
}

int main() {
    const char *url_payload = "payload=name=JohnDoe&age=30";
    char *start = strstr(url_payload, "payload=");
    if (start != NULL) {
        start += 8; // Skip "payload="
        char *name = parse_payload(start);
        printf("%s\n", name);
        free(name); // Free the allocated memory for the name
    }
    return 0;
}