#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} KeyValuePair;

typedef struct {
    KeyValuePair** entries;
    int count;
} Dictionary;

Dictionary* create_dictionary() {
    Dictionary* dict = (Dictionary*)malloc(sizeof(Dictionary));
    dict->entries = NULL;
    dict->count = 0;
    return dict;
}

void add_to_dictionary(Dictionary* dict, const char* key, const char* value) {
    KeyValuePair* entry = (KeyValuePair*)malloc(sizeof(KeyValuePair));
    entry->key = strdup(key);
    entry->value = strdup(value);

    dict->entries = realloc(dict->entries, sizeof(KeyValuePair*) * (dict->count + 1));
    dict->entries[dict->count] = entry;
    dict->count++;
}

char* get_from_dictionary(Dictionary* dict, const char* key) {
    for (int i = 0; i < dict->count; i++) {
        if (strcmp(dict->entries[i]->key, key) == 0) {
            return dict->entries[i]->value;
        }
    }
    return NULL;
}

void free_dictionary(Dictionary* dict) {
    for (int i = 0; i < dict->count; i++) {
        free(dict->entries[i]->key);
        free(dict->entries[i]->value);
        free(dict->entries[i]);
    }
    free(dict->entries);
    free(dict);
}

char* parse_payload(const char* payload) {
    Dictionary* params = create_dictionary();
    const char* token;
    char key[256];
    char value[256];

    for (token = strtok((char*)payload, "&"); token != NULL; token = strtok(NULL, "&")) {
        sscanf(token, "%[^=]=%s", key, value);
        add_to_dictionary(params, key, value);
    }

    char* name = get_from_dictionary(params, "name");
    free_dictionary(params);

    return name;
}

int main() {
    const char* payload = "/api?payload=name=JohnDoe&age=30";
    char* query_start = strstr(payload, "?") + 1;
    char* parsed_payload = parse_payload(query_start);

    if (parsed_payload != NULL) {
        printf("%s\n", parsed_payload);
        free(parsed_payload);
    } else {
        printf("Name not found in payload.\n");
    }

    return 0;
}