#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *pairs;
    int count;
} Dictionary;

void parse_query_string(const char *query, Dictionary *dict) {
    const char *token = query;
    while (1) {
        if (*token == '&' || *token == '\0') {
            if (token != query) {
                char *key = strdup(query);
                char *value = strchr(key, '=');
                if (value) {
                    *value++ = '\0';
                    dict->pairs[dict->count].key = key;
                    dict->pairs[dict->count].value = value;
                    dict->count++;
                } else {
                    free(strdup(key));
                }
            }
            if (*token == '\0') break;
            query = token + 1;
        }
        token++;
    }
}

char *get_value_from_dict(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->count; i++) {
        if (strcmp(dict->pairs[i].key, key) == 0) {
            return dict->pairs[i].value;
        }
    }
    return NULL;
}

void handle_api_request(const char *query_string) {
    Dictionary dict;
    dict.pairs = malloc(100 * sizeof(KeyValuePair));
    dict.count = 0;

    parse_query_string(query_string, &dict);

    const char *name_value = get_value_from_dict(&dict, "name");
    if (name_value != NULL) {
        printf("Content-Type: application/json\r\n\r\n{\"name\": \"%s\"}", name_value);
    } else {
        printf("Content-Type: application/json\r\n\r\n{\"error\": \"name parameter not found\"}");
    }

    for (int i = 0; i < dict.count; i++) {
        free(dict.pairs[i].key);
    }
    free(dict.pairs);
}

int main() {
    const char *query_string = "name=JohnDoe";
    handle_api_request(query_string);
    return 0;
}