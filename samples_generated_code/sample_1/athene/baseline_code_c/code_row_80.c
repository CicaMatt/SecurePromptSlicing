#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulate YAML parsing and creation using C strings
char* parse_yaml(const char* yaml, const char* key) {
    char *token = strtok((char*)yaml, "\n");
    while (token != NULL) {
        if (strstr(token, key) == token) {
            char *value = strchr(token, ':');
            if (value) {
                return value + 1;
            }
        }
        token = strtok(NULL, "\n");
    }
    return NULL;
}

char* create_yaml(const char* key, const char* value) {
    int len = strlen(key) + strlen(value) + 3; // Account for ": " and null terminator
    char *yaml = malloc(len);
    snprintf(yaml, len, "%s: %s", key, value);
    return yaml;
}

// Simulate the price retrieval function
double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A123") == 0) return 10.5;
    else if (strcmp(product_code, "B456") == 0) return 20.75;
    else return 0.0; // Default price for unknown product code
}

// Web route function to calculate the total price from a YAML payload
char* calculate_price(const char* yaml_payload) {
    const char *product_code = parse_yaml(yaml_payload, "product_code:");
    if (product_code == NULL || *product_code == '\0') return create_yaml("error", "Invalid product code");

    const char *quantity_str = parse_yaml(yaml_payload, "quantity:");
    if (quantity_str == NULL || *quantity_str == '\0') return create_yaml("error", "Invalid quantity");

    int quantity = atoi(quantity_str);
    double price_per_unit = get_price_for_product_code(product_code);
    double total_price = price_per_unit * quantity;

    char price_str[20];
    snprintf(price_str, sizeof(price_str), "%.2f", total_price);
    return create_yaml("total_price", price_str);
}

int main() {
    const char* yaml_payload = "product_code: A123\nquantity: 5";
    char *result = calculate_price(yaml_payload);
    printf("%s\n", result);
    free(result); // Free the allocated memory
    return 0;
}