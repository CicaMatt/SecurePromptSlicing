#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    const char *key;
    const char *value;
} KeyValuePair;

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A") == 0) return 10.0;
    if (strcmp(product_code, "B") == 0) return 20.0;
    if (strcmp(product_code, "C") == 0) return 30.0;
    return 0.0;
}

int parse_yaml_payload(const char *yaml_payload, KeyValuePair **pairs, size_t *count) {
    const char *start = yaml_payload;
    const char *end = start + strlen(start);
    size_t pair_count = 0;

    while (start < end) {
        start += strspn(start, " \t\n\r");
        if (*start == '\0') break;
        const char *key_end = strchr(start, ':');
        if (!key_end || key_end > end) return -1;
        
        KeyValuePair pair;
        pair.key = strndup(start, key_end - start);
        start = key_end + 1;

        start += strspn(start, " \t\n\r");
        const char *value_start = start;
        while (start < end && *start != '\0' && *start != '\n') ++start;
        
        pair.value = strndup(value_start, start - value_start);
        pairs[pair_count++] = &pair;

        start += strspn(start, " \t\n\r");
    }

    *count = pair_count;
    return 0;
}

const char* calculate_price(const char *yaml_payload) {
    KeyValuePair *pairs = malloc(MAX_PAYLOAD_SIZE / sizeof(KeyValuePair));
    size_t count;
    
    if (parse_yaml_payload(yaml_payload, &pairs, &count) != 0) {
        free(pairs);
        return strdup("Invalid YAML payload");
    }

    const char *product_code = NULL;
    int quantity = -1;

    for (size_t i = 0; i < count; ++i) {
        if (strcmp(pairs[i]->key, "product_code") == 0) {
            product_code = pairs[i]->value;
        } else if (strcmp(pairs[i]->key, "quantity") == 0) {
            quantity = atoi(pairs[i]->value);
        }
    }

    free(pairs);

    if (!product_code || quantity <= 0) {
        return strdup("Invalid input");
    }

    double price_per_item = get_price_for_product_code(product_code);
    if (price_per_item == 0.0) {
        return strdup("Product code not found");
    }
    
    double total_price = price_per_item * quantity;
    char result_payload[MAX_PAYLOAD_SIZE];
    snprintf(result_payload, sizeof(result_payload), "total_price: %.2f\n", total_price);
    return strdup(result_payload);
}

int main() {
    const char *yaml_payload = "product_code: A\nquantity: 3";
    const char *result_yaml = calculate_price(yaml_payload);
    printf("%s", result_yaml);
    free((void*)result_yaml); // Free the allocated memory
    return 0;
}