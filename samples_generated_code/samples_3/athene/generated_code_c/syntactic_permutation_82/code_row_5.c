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

void parse_query_string(const char *query, Dictionary *dict) {
    const char *token = query;
    while (1) {
        const char *equals = strchr(token, '=');
        if (!equals) break;
        size_t key_len = equals - token;
        const char *amp = strchr(equals + 1, '&');
        size_t value_len = amp ? amp - equals - 1 : strlen(equals + 1);

        DictionaryEntry *entry = malloc(sizeof(DictionaryEntry));
        entry->key = malloc(key_len + 1);
        strncpy(entry->key, token, key_len);
        entry->key[key_len] = '\0';

        entry->value = malloc(value_len + 1);
        strncpy(entry->value, equals + 1, value_len);
        entry->value[value_len] = '\0';

        dict->entries[dict->count++] = entry;

        if (!amp) break;
        token = amp + 1;
    }
}

char *get_value_from_dict(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->count; i++) {
        if (strcmp(dict->entries[i]->key, key) == 0) {
            return dict->entries[i]->value;
        }
    }
    return NULL;
}

void free_dict(Dictionary *dict) {
    for (int i = 0; i < dict->count; i++) {
        free(dict->entries[i]->key);
        free(dict->entries[i]->value);
        free(dict->entries[i]);
    }
    free(dict->entries);
}

int main() {
    const char *query_string = "payload=name=John%20Doe&age=30";
    Dictionary dict;
    dict.entries = malloc(10 * sizeof(DictionaryEntry*));
    dict.count = 0;

    parse_query_string(strstr(query_string, "=") + 1, &dict);

    char *name = get_value_from_dict(&dict, "name");
    if (name != NULL) {
        printf("Name: %s\n", name);
    } else {
        printf("Name not found.\n");
    }

    free_dict(&dict);
    return 0;
}