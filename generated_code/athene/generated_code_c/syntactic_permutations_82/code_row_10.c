#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

KeyValuePair* parse_query_string(const char *query, int *count) {
    const char *delims = "&";
    char *token, *kv_delim, *str_dup;
    str_dup = strdup(query);
    if (!str_dup) return NULL;

    KeyValuePair *pairs = malloc(100 * sizeof(KeyValuePair));
    if (!pairs) {
        free(str_dup);
        return NULL;
    }

    int i = 0;
    for (token = strtok(str_dup, delims); token && i < 100; token = strtok(NULL, delims)) {
        kv_delim = strchr(token, '=');
        if (kv_delim) {
            *kv_delim = '\0';
            pairs[i].key = strdup(token);
            pairs[i].value = strdup(kv_delim + 1);
            i++;
        }
    }

    free(str_dup);
    *count = i;
    return pairs;
}

char* get_name_from_payload(const char *query) {
    int count;
    KeyValuePair *pairs = parse_query_string(query, &count);

    for (int i = 0; i < count; i++) {
        if (strcmp(pairs[i].key, "name") == 0) {
            char *result = strdup(pairs[i].value);
            for (int j = 0; j < count; j++) {
                free(pairs[j].key);
                free(pairs[j].value);
            }
            free(pairs);
            return result;
        }
    }

    for (int i = 0; i < count; i++) {
        free(pairs[i].key);
        free(pairs[i].value);
    }
    free(pairs);

    return NULL;
}

int main() {
    const char *query = "payload=name=John&age=30";
    char *name = get_name_from_payload(query);
    if (name) {
        printf("Name: %s\n", name);
        free(name);
    } else {
        printf("Name not found.\n");
    }
    return 0;
}