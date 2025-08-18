#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

typedef struct {
    char key[50];
    char value[50];
} KeyValuePair;

typedef struct {
    KeyValuePair *items;
    size_t count;
} Dictionary;

void add_to_dictionary(Dictionary *dict, const char *key, const char *value) {
    dict->count++;
    dict->items = realloc(dict->items, sizeof(KeyValuePair) * dict->count);
    strcpy(dict->items[dict->count - 1].key, key);
    strcpy(dict->items[dict->count - 1].value, value);
}

char* get_value_from_dictionary(Dictionary *dict, const char *key) {
    for (size_t i = 0; i < dict->count; ++i) {
        if (strcmp(dict->items[i].key, key) == 0) {
            return dict->items[i].value;
        }
    }
    return NULL;
}

void free_dictionary(Dictionary *dict) {
    free(dict->items);
    dict->items = NULL;
    dict->count = 0;
}

char* extract_payload(const char *url) {
    const char *start = strstr(url, "payload=");
    if (start == NULL) {
        return NULL;
    }
    start += strlen("payload=");

    const char *end = strchr(start, '&');
    size_t len = end ? (size_t)(end - start) : strlen(start);
    
    char *payload_str = malloc(len + 1);
    strncpy(payload_str, start, len);
    payload_str[len] = '\0';
    return payload_str;
}

int parse_payload(const char *payload_str, Dictionary *dict) {
    const char *start = payload_str;
    while (*start) {
        const char *key_start = strchr(start, ' ');
        if (key_start == NULL) break;
        
        const char *value_start = strchr(key_start + 1, ' ');
        if (value_start == NULL) break;

        size_t key_len = key_start - start;
        size_t value_len = value_start - key_start - 1;

        char key[50], value[50];
        strncpy(key, start, key_len);
        key[key_len] = '\0';
        strncpy(value, key_start + 1, value_len);
        value[value_len] = '\0';

        add_to_dictionary(dict, key, value);

        start = value_start + 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <url>\n", argv[0]);
        return 1;
    }

    const char *url = argv[1];
    Dictionary dict = {NULL, 0};

    char *payload_str = extract_payload(url);
    if (!payload_str) {
        printf("Payload not found\n");
        return 1;
    }
    
    parse_payload(payload_str, &dict);

    char* name_value = get_value_from_dictionary(&dict, "name");
    if (name_value) {
        printf("%s\n", name_value);
    } else {
        printf("Name not found in payload\n");
    }

    free(payload_str);
    free_dictionary(&dict);

    return 0;
}