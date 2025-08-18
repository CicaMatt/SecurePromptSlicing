#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[50];
    char value[50];
} KeyValuePair;

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A001") == 0) return 10.0;
    if (strcmp(product_code, "B002") == 0) return 20.5;
    if (strcmp(product_code, "C003") == 0) return 15.75;
    return 0.0; // Default price for unknown product codes
}

int parse_yaml(const char *yaml_str, KeyValuePair **pairs, int max_pairs) {
    const char *start = yaml_str;
    const char *end = NULL;
    int count = 0;

    while (count < max_pairs && (end = strchr(start, '\n')) != NULL) {
        size_t length = end - start;
        if (length > 0 && start[length - 1] == ':') {
            strncpy((*pairs)[count].key, start, length - 2);
            (*pairs)[count].key[length - 2] = '\0';
            start += length + 1; // Skip ':' and newline
            end = strchr(start, '\n');
            if (end) {
                size_t value_length = end - start;
                strncpy((*pairs)[count].value, start, value_length);
                (*pairs)[count].value[value_length] = '\0';
                count++;
                start = end + 1; // Move to the next line
            }
        } else {
            break;
        }
    }

    return count;
}

double calculate_price(const char *yaml_payload) {
    KeyValuePair pairs[10];
    int pair_count = parse_yaml(yaml_payload, &pairs, sizeof(pairs) / sizeof(pairs[0]));

    const char *product_code_key = "product_code";
    const char *quantity_key = "quantity";

    for (int i = 0; i < pair_count; ++i) {
        if (strcmp(pairs[i].key, product_code_key) == 0) {
            double price_per_item = get_price_for_product_code(pairs[i].value);
            for (int j = 0; j < pair_count; ++j) {
                if (strcmp(pairs[j].key, quantity_key) == 0) {
                    int quantity = atoi(pairs[j].value);
                    return price_per_item * quantity;
                }
            }
        }
    }

    return 0.0; // Return 0 if product code or quantity is not found
}

int main() {
    const char *yaml_payload = 
        "product_code: A001\n"
        "quantity: 3\n";

    double total_price = calculate_price(yaml_payload);
    
    printf("total_price: %.2f\n", total_price);

    return 0;
}