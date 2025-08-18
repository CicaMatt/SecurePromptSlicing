#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *key;
    char *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry **entries;
    int count;
} Dictionary;

Dictionary* create_dictionary() {
    Dictionary *dict = (Dictionary*) malloc(sizeof(Dictionary));
    dict->entries = NULL;
    dict->count = 0;
    return dict;
}

void add_entry(Dictionary *dict, const char *key, const char *value) {
    DictionaryEntry *entry = (DictionaryEntry*) malloc(sizeof(DictionaryEntry));
    entry->key = strdup(key);
    entry->value = strdup(value);

    dict->entries = (DictionaryEntry**) realloc(dict->entries, sizeof(DictionaryEntry*) * (dict->count + 1));
    dict->entries[dict->count++] = entry;
}

char* get_value(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->count; ++i) {
        if (strcmp(dict->entries[i]->key, key) == 0) {
            return dict->entries[i]->value;
        }
    }
    return NULL;
}

void parse_query_string(const char *query, Dictionary *dict) {
    const char *param = query;
    while (*param) {
        const char *equals = strchr(param, '=');
        if (equals == NULL) break;

        int key_len = equals - param;
        char *key = malloc(key_len + 1);
        strncpy(key, param, key_len);
        key[key_len] = '\0';

        const char *value = equals + 1;
        const char *ampersand = strchr(value, '&');
        if (ampersand != NULL) {
            int value_len = ampersand - value;
            char *val = malloc(value_len + 1);
            strncpy(val, value, value_len);
            val[value_len] = '\0';
            add_entry(dict, key, val);
            param = ampersand + 1;
        } else {
            add_entry(dict, key, strdup(value));
            break;
        }
    }
}

int main() {
    // Simulate a web request with a query string
    const char *query_string = "payload={%22name%22:%22John%20Doe%22}";
    
    Dictionary *dict = create_dictionary();
    parse_query_string(query_string, dict);

    char *payload = get_value(dict, "payload");
    if (payload != NULL) {
        // Simplified JSON parsing for demonstration
        const char name_key[] = "\"name\":\"";
        const size_t key_len = strlen(name_key);
        const char *start = strstr(payload, name_key);
        if (start != NULL) {
            start += key_len;
            const char *end = strchr(start, '\"');
            if (end != NULL) {
                int name_len = end - start;
                char name[name_len + 1];
                strncpy(name, start, name_len);
                name[name_len] = '\0';
                printf("Name: %s\n", name);
            }
        }
    }

    // Free allocated memory
    for (int i = 0; i < dict->count; ++i) {
        free(dict->entries[i]->key);
        free(dict->entries[i]->value);
        free(dict->entries[i]);
    }
    free(dict->entries);
    free(dict);

    return 0;
}