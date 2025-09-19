#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry **entries;
    int count;
} Dictionary;

Dictionary* create_dictionary() {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    dict->entries = NULL;
    dict->count = 0;
    return dict;
}

void add_entry(Dictionary *dict, const char *key, const char *value) {
    DictionaryEntry *entry = (DictionaryEntry*)malloc(sizeof(DictionaryEntry));
    entry->key = strdup(key);
    entry->value = strdup(value);
    dict->entries = realloc(dict->entries, sizeof(DictionaryEntry*) * (dict->count + 1));
    dict->entries[dict->count++] = entry;
}

char* get_value(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->count; i++) {
        if (strcmp(dict->entries[i]->key, key) == 0) {
            return dict->entries[i]->value;
        }
    }
    return NULL;
}

void free_dictionary(Dictionary *dict) {
    for (int i = 0; i < dict->count; i++) {
        free(dict->entries[i]->key);
        free(dict->entries[i]->value);
        free(dict->entries[i]);
    }
    free(dict->entries);
    free(dict);
}

char* parse_payload(const char *payload) {
    Dictionary *dict = create_dictionary();
    const char *token, *context;
    token = strtok_r(payload, "&", &context);
    while (token != NULL) {
        char *key = strtok_r((char*)token, "=", &context);
        char *value = strtok_r(NULL, "&", &context);
        if (key && value) {
            add_entry(dict, key, value);
        }
        token = strtok_r(NULL, "&", &context);
    }

    char *name_value = get_value(dict, "name");
    free_dictionary(dict);

    return name_value;
}

int main() {
    const char *payload = "name=John&age=30";
    char *name = parse_payload(payload);
    if (name) {
        printf("%s\n", name);
        free(name);
    } else {
        printf("Name not found in payload.\n");
    }
    return 0;
}