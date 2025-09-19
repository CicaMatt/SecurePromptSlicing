#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a simple structure for key-value pairs (dictionary entry)
typedef struct {
    char *key;
    char *value;
} KeyValuePair;

// Function to create and return a new key-value pair
KeyValuePair* make_pair(const char *key, const char *value) {
    KeyValuePair *pair = malloc(sizeof(KeyValuePair));
    if (!pair) return NULL;
    pair->key = strdup(key);
    pair->value = strdup(value);
    return pair;
}

// Function to add a key-value pair to the dictionary
void add_pair_to_dict(KeyValuePair **dict, size_t *size, const char *key, const char *value) {
    // Increase the size of the array and reallocate memory
    KeyValuePair **new_dict = realloc(dict, (*size + 1) * sizeof(KeyValuePair *));
    if (!new_dict) return;
    dict = new_dict;

    // Add the new key-value pair to the dictionary
    dict[*size] = make_pair(key, value);
    (*size)++;
}

// Function to find a value by key in the dictionary
char* get_value_from_dict(KeyValuePair **dict, size_t size, const char *key) {
    for (size_t i = 0; i < size; i++) {
        if (strcmp(dict[i]->key, key) == 0) {
            return dict[i]->value;
        }
    }
    return NULL;
}

// Function to free the dictionary
void free_dict(KeyValuePair **dict, size_t size) {
    for (size_t i = 0; i < size; i++) {
        free(dict[i]->key);
        free(dict[i]->value);
        free(dict[i]);
    }
    free(dict);
}

int main() {
    // Example URL payload: "param1=value1&name=JohnDoe"
    char url_payload[] = "param1=value1&name=JohnDoe";

    KeyValuePair *dictionary[10];  // Array to hold dictionary entries
    size_t dict_size = 0;

    // Parse the URL payload and load into dictionary
    char *token = strtok(url_payload, "&");
    while (token) {
        char *key_value_pair = strdup(token);
        char *equal_sign = strchr(key_value_pair, '=');

        if (equal_sign) {
            *equal_sign = '\0';  // Split the string at '='
            add_pair_to_dict(dictionary, &dict_size, key_value_pair, equal_sign + 1);
        }

        free(key_value_pair);
        token = strtok(NULL, "&");
    }

    // Retrieve and print the value associated with "name"
    char *name_value = get_value_from_dict(dictionary, dict_size, "name");
    if (name_value) {
        printf("Name: %s\n", name_value);
    } else {
        printf("Name not found.\n");
    }

    // Free allocated memory
    free_dict(dictionary, dict_size);

    return 0;
}