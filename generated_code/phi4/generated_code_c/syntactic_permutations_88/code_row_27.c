#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple YAML parser for demonstration purposes
typedef struct {
    char key[50];
    int value;
} KeyValuePair;

int parse_yaml(const char *yaml, KeyValuePair *pairs, int max_pairs) {
    const char *start = yaml;
    int pairs_count = 0;

    while (*start && pairs_count < max_pairs) {
        const char *key_start = strpbrk(start, ":-");
        if (!key_start) break;

        if (strchr(key_start, ':')) {
            key_start++;
        } else {
            key_start += 2;
        }

        const char *key_end = strchr(key_start, '\n');
        const char *value_start = key_end + 1;
        const char *value_end = strpbrk(value_start, "\n");

        if (key_end && value_end) {
            strncpy(pairs[pairs_count].key, key_start, key_end - key_start);
            pairs[pairs_count].key[key_end - key_start] = '\0';

            pairs[pairs_count].value = atoi(value_start);

            start = value_end;
            pairs_count++;
        } else {
            break;
        }
    }

    return pairs_count;
}

double calculate_price(const char *yaml_payload, const double product_prices[]) {
    KeyValuePair pairs[10];
    int pairs_count = parse_yaml(yaml_payload, pairs, 10);
    double total_price = 0.0;

    for (int i = 0; i < pairs_count; ++i) {
        if (strcmp(pairs[i].key, "product_code") == 0 || strcmp(pairs[i].key, "quantity") == 0) {
            // Assuming product_prices is indexed by ASCII value of 'a' to 'z'
            const char *code = strchr(yaml_payload, ':') + 2;
            const char *end = strpbrk(code, "\n");
            if (end) *end = '\0';

            int quantity_index = -1;
            for (int j = 0; j < pairs_count; ++j) {
                if (strcmp(pairs[j].key, "quantity") == 0) {
                    quantity_index = j;
                    break;
                }
            }

            if (quantity_index != -1 && code[0] >= 'a' && code[0] <= 'z') {
                total_price = product_prices[code[0] - 'a'] * pairs[quantity_index].value;
            }
        }
    }

    return total_price;
}

int main() {
    const char *yaml_payload = "product_code: a\n"
                               "quantity: 3\n";

    double product_prices[] = {10.0, 20.0, 30.0}; // Prices for products 'a', 'b', 'c'

    double price = calculate_price(yaml_payload, product_prices);
    printf("Total Price: %.2f\n", price);

    return 0;
}