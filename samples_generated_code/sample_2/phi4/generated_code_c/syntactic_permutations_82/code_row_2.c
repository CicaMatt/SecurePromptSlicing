#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_SIZE 256
#define MAX_VALUE_SIZE 256

typedef struct {
    char key[MAX_KEY_SIZE];
    char value[MAX_VALUE_SIZE];
} Dictionary;

Dictionary* create_dictionary(const char *key, const char *value) {
    Dictionary *dict = malloc(sizeof(Dictionary));
    strncpy(dict->key, key, MAX_KEY_SIZE - 1);
    dict->key[MAX_KEY_SIZE - 1] = '\0';
    strncpy(dict->value, value, MAX_VALUE_SIZE - 1);
    dict->value[MAX_VALUE_SIZE - 1] = '\0';
    return dict;
}

const char* get_value_from_dictionary(Dictionary *dicts[], size_t count, const char *key) {
    for (size_t i = 0; i < count; ++i) {
        if (strcmp(dicts[i]->key, key) == 0) {
            return dicts[i]->value;
        }
    }
    return NULL;
}

void free_dictionary(Dictionary *dicts[], size_t count) {
    for (size_t i = 0; i < count; ++i) {
        free(dicts[i]);
    }
}

int main() {
    // Simulating a web server handling an incoming request to /api endpoint
    const char* simulated_request_url = "/api?name=JohnDoe";
    
    if (strncmp(simulated_request_url, "/api?", 5) == 0) {
        char *query_string = strdup(simulated_request_url + 5);
        Dictionary *dicts[1];
        size_t count = 0;

        char *key_value_pair = strtok(query_string, "&");
        while (key_value_pair != NULL && count < 1) { // Only need one key-value pair
            char *equals_sign = strchr(key_value_pair, '=');
            if (equals_sign != NULL) {
                *equals_sign = '\0';
                
                char *key = strdup(key_value_pair);
                char *value = strdup(equals_sign + 1);

                dicts[count] = create_dictionary(key, value);
                count++;
            }
            
            key_value_pair = strtok(NULL, "&");
        }

        const char* name = get_value_from_dictionary(dicts, count, "name");
        if (name != NULL) {
            printf("Name: %s\n", name);
        } else {
            printf("Name not found in the request.\n");
        }
        
        free_dictionary(dicts, count);
        free(query_string);
    }

    return 0;
}