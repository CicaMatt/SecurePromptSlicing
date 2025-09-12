#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

KeyValuePair* parse_query_string(const char *query, int *count) {
    const char *token = query;
    int n = 0;
    while (1) {
        if (*token == '&' || *token == '\0') {
            n++;
            if (*token == '\0') break;
            token++;
        } else {
            token++;
        }
    }

    KeyValuePair *pairs = malloc(n * sizeof(KeyValuePair));
    *count = n;

    token = query;
    for (int i = 0; i < n; i++) {
        pairs[i].key = NULL;
        pairs[i].value = NULL;

        const char *equals = strchr(token, '=');
        if (equals) {
            int key_len = equals - token;
            pairs[i].key = malloc(key_len + 1);
            strncpy(pairs[i].key, token, key_len);
            pairs[i].key[key_len] = '\0';

            token = equals + 1;
            const char *amp_or_end = strchr(token, '&');
            if (amp_or_end) {
                int value_len = amp_or_end - token;
                pairs[i].value = malloc(value_len + 1);
                strncpy(pairs[i].value, token, value_len);
                pairs[i].value[value_len] = '\0';
                token = amp_or_end + 1;
            } else {
                pairs[i].value = strdup(token);
                break;
            }
        }
    }

    return pairs;
}

char* get_name_from_payload(const char *url) {
    const char *query_start = strchr(url, '?');
    if (!query_start) return NULL;

    int count;
    KeyValuePair *pairs = parse_query_string(query_start + 1, &count);

    for (int i = 0; i < count; i++) {
        if (strcmp(pairs[i].key, "name") == 0) {
            char *name = strdup(pairs[i].value);
            for (int j = 0; j < count; j++) {
                free(pairs[j].key);
                free(pairs[j].value);
            }
            free(pairs);
            return name;
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
    const char *url = "http://example.com/app?payload=name%3DJohn%26age%3D30";
    char *name = get_name_from_payload(url);
    if (name) {
        printf("Name: %s\n", name);
        free(name);
    } else {
        printf("No name found in payload.\n");
    }
    return 0;
}