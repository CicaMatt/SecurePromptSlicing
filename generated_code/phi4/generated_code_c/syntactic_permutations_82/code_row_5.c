#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char key[MAX_PAYLOAD_SIZE];
    char value[MAX_PAYLOAD_SIZE];
} KeyValuePair;

typedef struct {
    int size;
    KeyValuePair pairs[MAX_PAYLOAD_SIZE / 2];
} Dictionary;

int parse_url(const char *url, char **payload) {
    const char *start = strstr(url, "?");
    if (!start) return -1;
    
    start++; // Move past '?'
    const char *end = strchr(start, '&');
    if (end) {
        int len = end - start;
        *payload = malloc(len + 1);
        strncpy(*payload, start, len);
        (*payload)[len] = '\0';
    } else {
        size_t len = strlen(start);
        *payload = malloc(len + 1);
        strcpy(*payload, start);
    }
    
    return 0;
}

int load_payload_into_dict(const char *payload, Dictionary *dict) {
    dict->size = 0;
    const char *start = payload;
    char *end;

    while ((end = strchr(start, '&')) != NULL || (end = strchr(start, '\0'))) {
        int len = end - start;
        KeyValuePair pair;
        if (strchr(start, '=') == NULL) break; // No '=' in a valid key=value
        char *equals_pos = strchr(start, '=');
        
        strncpy(pair.key, start, equals_pos - start);
        pair.key[equals_pos - start] = '\0';
        
        strcpy(pair.value, equals_pos + 1);
        if (len < strlen(pair.value) + 1) break; // Error handling
        
        dict->pairs[dict->size++] = pair;
        start = end + 1;
    }
    
    return 0;
}

int get_value_from_dict(Dictionary *dict, const char *key, char *result, int result_size) {
    for (int i = 0; i < dict->size; ++i) {
        if (strcmp(dict->pairs[i].key, key) == 0) {
            strncpy(result, dict->pairs[i].value, result_size - 1);
            result[result_size - 1] = '\0';
            return 0;
        }
    }
    return -1;
}

void handle_request(const char *url) {
    char *payload = NULL;
    if (parse_url(url, &payload) == 0) {
        Dictionary dict;
        load_payload_into_dict(payload, &dict);

        char name_value[256];
        if (get_value_from_dict(&dict, "name", name_value, sizeof(name_value)) == 0) {
            printf("Name: %s\n", name_value);
        } else {
            printf("Name parameter not found.\n");
        }

        free(payload);
    }
}

int main() {
    const char *url = "/api?name=JohnDoe&age=30";
    handle_request(url);
    return 0;
}