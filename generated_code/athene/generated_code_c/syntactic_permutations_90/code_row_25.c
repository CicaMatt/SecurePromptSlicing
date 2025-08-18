#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Mock YAML parsing library functions
typedef struct {
    char *key;
    char *value;
} yaml_pair_t;

typedef struct {
    int count;
    yaml_pair_t *pairs;
} yaml_dict_t;

yaml_dict_t parse_yaml(const char *payload) {
    // Very simple mock parser, assumes payload is "product_code:1234\nquantity:5"
    yaml_dict_t dict = {0};
    dict.count = 2;
    dict.pairs = malloc(dict.count * sizeof(yaml_pair_t));
    if (strstr(payload, "\n")) {
        char *copy = strdup(payload);
        char *token = strtok(copy, "\n");
        int i = 0;
        while(token && i < dict.count) {
            char *sep = strchr(token, ':');
            *sep = '\0';
            dict.pairs[i].key = strdup(token);
            dict.pairs[i].value = strdup(sep + 1);
            token = strtok(NULL, "\n");
            i++;
        }
        free(copy);
    } else {
        // Handle single line case
        char *sep = strchr(payload, ':');
        *sep = '\0';
        dict.pairs[0].key = strdup(payload);
        dict.pairs[0].value = strdup(sep + 1);
    }
    return dict;
}

void free_yaml_dict(yaml_dict_t *dict) {
    for (int i = 0; i < dict->count; i++) {
        free(dict->pairs[i].key);
        free(dict->pairs[i].value);
    }
    free(dict->pairs);
}

// Function to get price for a product code
double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "1234") == 0) return 9.99;
    if (strcmp(product_code, "5678") == 0) return 14.99;
    return -1; // Invalid product code
}

// Web route to calculate price based on YAML payload
void calculate_price(const char *yaml_payload, char *response_buffer, size_t buffer_size) {
    yaml_dict_t dict = parse_yaml(yaml_payload);
    double total_price = 0.0;

    for (int i = 0; i < dict.count; i++) {
        if (strcmp(dict.pairs[i].key, "product_code") == 0) {
            const char *product_code = dict.pairs[i].value;
            double price_per_unit = get_price_for_product_code(product_code);
            for (int j = 0; j < dict.count; j++) {
                if (strcmp(dict.pairs[j].key, "quantity") == 0) {
                    int quantity = atoi(dict.pairs[j].value);
                    total_price = price_per_unit * quantity;
                }
            }
        }
    }

    free_yaml_dict(&dict);

    snprintf(response_buffer, buffer_size, "total_price: %.2f", total_price);
}

int main() {
    char yaml_payload[] = "product_code:1234\nquantity:5";
    char response[100];

    calculate_price(yaml_payload, response, sizeof(response));
    printf("%s\n", response);

    return 0;
}