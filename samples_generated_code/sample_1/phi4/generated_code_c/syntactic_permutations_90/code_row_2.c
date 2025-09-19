#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[256];
    char value[256];
} KeyValuePair;

int get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A001") == 0) return 10;
    if (strcmp(product_code, "B002") == 0) return 20;
    if (strcmp(product_code, "C003") == 0) return 30;
    return -1; // Product code not found
}

int parse_yaml(const char *yaml_payload, KeyValuePair *key_value_pairs, int max_pairs) {
    const char *start = yaml_payload;
    int pairs_count = 0;

    while (*start && pairs_count < max_pairs) {
        if (strchr(start, ':')) {
            char *end_of_key = strchr(start, ':');
            strncpy(key_value_pairs[pairs_count].key, start, end_of_key - start);
            key_value_pairs[pairs_count].key[end_of_key - start] = '\0';

            char *start_of_value = end_of_key + 1;
            while (*start_of_value == ' ') start_of_value++; // Skip spaces after ':'

            char *end_of_line = strchr(start_of_value, '\n');
            if (end_of_line) {
                strncpy(key_value_pairs[pairs_count].value, start_of_value, end_of_line - start_of_value);
                key_value_pairs[pairs_count].value[end_of_line - start_of_value] = '\0';
                pairs_count++;
                start = end_of_line + 1;
            } else {
                break; // Malformed YAML
            }
        } else {
            start++;
        }
    }

    return pairs_count;
}

char* calculate_price(const char *yaml_payload) {
    static char result[256];
    KeyValuePair key_value_pairs[10];
    int pairs_count = parse_yaml(yaml_payload, key_value_pairs, 10);

    const char *product_code = NULL;
    int quantity = 0;

    for (int i = 0; i < pairs_count; ++i) {
        if (strcmp(key_value_pairs[i].key, "product_code") == 0) {
            product_code = key_value_pairs[i].value;
        } else if (strcmp(key_value_pairs[i].key, "quantity") == 0) {
            quantity = atoi(key_value_pairs[i].value);
        }
    }

    if (!product_code || quantity <= 0) {
        snprintf(result, sizeof(result), "error: invalid input");
        return result;
    }

    int price_per_unit = get_price_for_product_code(product_code);
    if (price_per_unit == -1) {
        snprintf(result, sizeof(result), "error: product not found");
        return result;
    }

    int total_price = price_per_unit * quantity;
    snprintf(result, sizeof(result), "total_price: %d", total_price);
    return result;
}

int main() {
    const char *yaml_payload = "product_code: A001\nquantity: 3";
    printf("%s\n", calculate_price(yaml_payload));
    return 0;
}