#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[50];
    char value[50];
} KeyValuePair;

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "P001") == 0)
        return 10.99;
    else if (strcmp(product_code, "P002") == 0)
        return 15.49;
    else
        return 0.0;
}

int parse_yaml(const char* yaml_str, KeyValuePair** kv_pairs) {
    int count = 0;
    const char *start = yaml_str;
    
    while (1) {
        const char *key_start = strstr(start, "key:");
        if (!key_start)
            break;

        key_start += 4; // Move past "key:"
        const char *key_end = strchr(key_start, '\n');
        if (!key_end)
            break;

        const char *value_start = strstr(key_end + 1, "value:");
        if (!value_start)
            break;

        value_start += 6; // Move past "value:"
        const char *value_end = strchr(value_start, '\n');
        if (!value_end)
            break;

        KeyValuePair kv;
        strncpy(kv.key, key_start, key_end - key_start);
        kv.key[key_end - key_start] = '\0';
        strncpy(kv.value, value_start, value_end - value_start);
        kv.value[value_end - value_start] = '\0';

        (*kv_pairs)[count++] = kv;

        start = value_end + 1;
    }

    return count;
}

char* calculate_price(const char* yaml_payload) {
    static KeyValuePair kv_pairs[10];
    int pair_count = parse_yaml(yaml_payload, &kv_pairs);

    const char *product_code_key = "key: product_code";
    const char *quantity_key = "key: quantity";

    char *product_code = NULL;
    int quantity = 0;

    for (int i = 0; i < pair_count; ++i) {
        if (strcmp(kv_pairs[i].key, "product_code") == 0) {
            product_code = strdup(kv_pairs[i].value);
        }
        if (strcmp(kv_pairs[i].key, "quantity") == 0) {
            quantity = atoi(kv_pairs[i].value);
        }
    }

    double price_per_unit = get_price_for_product_code(product_code);
    char *result_yaml = malloc(100);

    snprintf(result_yaml, 100, "total_price: %f", price_per_unit * quantity);
    free(product_code);

    return result_yaml;
}

int main() {
    const char* yaml_payload =
        "key: product_code\n"
        "value: P001\n"
        "key: quantity\n"
        "value: 3\n";

    char* result = calculate_price(yaml_payload);
    printf("%s\n", result);

    return 0;
}