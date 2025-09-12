#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 256

typedef struct {
    char key[MAX_STRING_LEN];
    char value[MAX_STRING_LEN];
} KeyValuePair;

int get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "123") == 0) return 10;
    if (strcmp(product_code, "456") == 0) return 20;
    if (strcmp(product_code, "789") == 0) return 30;
    return -1; // Unknown product code
}

int parse_yaml(const char *yaml_str, KeyValuePair pairs[], int max_pairs) {
    const char *start = yaml_str;
    int count = 0;

    while (*start && count < max_pairs) {
        char key[MAX_STRING_LEN] = {0};
        char value[MAX_STRING_LEN] = {0};

        // Extract key
        start += strspn(start, " \t\n");
        const char *key_start = start;
        if (strchr(key_start, ':') == NULL || strchr(key_start, ' ') == NULL) break;
        size_t key_len = strcspn(key_start, ": ");
        strncpy(key, key_start, key_len);
        
        // Extract value
        start += strcspn(start, " \t\n") + 1; // Skip ':'
        const char *value_start = start;
        start += strcspn(start, "\n");
        size_t value_len = start - value_start;
        strncpy(value, value_start, value_len);

        pairs[count++] = (KeyValuePair){.key = key, .value = value};
        start += strspn(start, "\n") + 1; // Move to next line
    }
    return count;
}

char* calculate_price(const char *yaml_query) {
    static char result[MAX_STRING_LEN];
    KeyValuePair pairs[10];
    int pair_count = parse_yaml(yaml_query, pairs, 10);
    
    const char *product_code = NULL;
    const char *quantity_str = NULL;

    for (int i = 0; i < pair_count; ++i) {
        if (strcmp(pairs[i].key, "product_code") == 0)
            product_code = pairs[i].value;
        else if (strcmp(pairs[i].key, "quantity") == 0)
            quantity_str = pairs[i].value;
    }

    if (!product_code || !quantity_str) {
        snprintf(result, sizeof(result), "query: invalid\n");
        return result;
    }

    int price_per_unit = get_price_for_product_code(product_code);
    if (price_per_unit == -1) {
        snprintf(result, sizeof(result), "query: unknown product code\n");
        return result;
    }
    
    int quantity = atoi(quantity_str);
    int total_price = price_per_unit * quantity;

    snprintf(result, sizeof(result), 
             "product_code: %s\n"
             "quantity: %d\n"
             "total_price: %d\n",
             product_code, quantity, total_price);

    return result;
}

int main() {
    const char *yaml_query = "product_code: 123\nquantity: 2\n";
    printf("%s", calculate_price(yaml_query));
    return 0;
}