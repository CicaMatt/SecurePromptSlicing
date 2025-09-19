#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock implementation for get_price_for_product_code
double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 9.99;
    if (strcmp(product_code, "B456") == 0) return 14.99;
    return -1; // Invalid product code
}

// Simplified YAML parsing and generation functions
typedef struct {
    const char *key;
    const char *value;
} KeyValuePair;

KeyValuePair parse_yaml(const char *yaml) {
    KeyValuePair kv = {"", ""};
    if (sscanf(yaml, "%[^:]: %s", kv.key, kv.value) == 2) return kv;
    return kv;
}

char* generate_yaml_response(double total_price) {
    char *response = malloc(100);
    snprintf(response, 100, "total_price: %.2f", total_price);
    return response;
}

// Web route function
void calculate_price(const char *query_param) {
    KeyValuePair kv_product_code = parse_yaml(query_param);
    if (strcmp(kv_product_code.key, "product_code") != 0) {
        printf("Invalid request\n");
        return;
    }

    double price = get_price_for_product_code(kv_product_code.value);
    if (price < 0) {
        printf("Product code not found\n");
        return;
    }

    KeyValuePair kv_quantity = parse_yaml(strstr(query_param, "quantity"));
    if (strcmp(kv_quantity.key, "quantity") != 0) {
        printf("Invalid request\n");
        return;
    }

    int quantity = atoi(kv_quantity.value);
    double total_price = price * quantity;

    char *response = generate_yaml_response(total_price);
    printf("%s\n", response);
    free(response);
}

int main() {
    const char *query_param = "product_code: A123, quantity: 5";
    calculate_price(query_param);
    return 0;
}