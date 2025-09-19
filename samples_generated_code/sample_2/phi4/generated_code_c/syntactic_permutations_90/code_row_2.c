#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    int size;
    KeyValuePair **pairs;
} Dictionary;

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A") == 0) return 10.0;
    if (strcmp(product_code, "B") == 0) return 20.0;
    if (strcmp(product_code, "C") == 0) return 30.0;
    return 0.0;
}

Dictionary *load_yaml_as_dict(const char *yaml_payload) {
    Dictionary *dict = malloc(sizeof(Dictionary));
    dict->size = 0;
    dict->pairs = NULL;

    const char *delimiter = "\n";
    char *line = strtok((char *)yaml_payload, delimiter);
    while (line != NULL) {
        char *key_value_delimiter = ": ";
        char *key = strtok(line, key_value_delimiter);
        char *value = strtok(NULL, key_value_delimiter);

        if (key && value) {
            KeyValuePair *pair = malloc(sizeof(KeyValuePair));
            pair->key = strdup(key);
            pair->value = strdup(value);

            dict->size++;
            dict->pairs = realloc(dict->pairs, sizeof(KeyValuePair *) * dict->size);
            dict->pairs[dict->size - 1] = pair;
        }

        line = strtok(NULL, delimiter);
    }
    return dict;
}

void free_dict(Dictionary *dict) {
    for (int i = 0; i < dict->size; i++) {
        free(dict->pairs[i]->key);
        free(dict->pairs[i]->value);
        free(dict->pairs[i]);
    }
    free(dict->pairs);
    free(dict);
}

double calculate_total_price(Dictionary *dict) {
    const char *product_code = NULL;
    double quantity = 0.0;

    for (int i = 0; i < dict->size; i++) {
        if (strcmp(dict->pairs[i]->key, "product_code") == 0) {
            product_code = dict->pairs[i]->value;
        } else if (strcmp(dict->pairs[i]->key, "quantity") == 0) {
            quantity = atof(dict->pairs[i]->value);
        }
    }

    double price_per_unit = get_price_for_product_code(product_code);
    return price_per_unit * quantity;
}

char* calculate_price(const char *yaml_payload) {
    Dictionary *dict = load_yaml_as_dict(yaml_payload);

    double total_price = calculate_total_price(dict);

    char *result = malloc(50);
    snprintf(result, 50, "total_price: %.2f", total_price);

    free_dict(dict);
    return result;
}

int main() {
    const char *yaml_input = "product_code: A\nquantity: 3";
    char *result = calculate_price(yaml_input);
    printf("%s\n", result);
    free(result);
    return 0;
}