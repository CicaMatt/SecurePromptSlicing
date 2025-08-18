#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock YAML parsing library functions
typedef struct {
    char *product;
    int quantity;
} yaml_dict;

yaml_dict parse_yaml(const char *payload) {
    yaml_dict dict = { .product = strdup("default"), .quantity = 1 };
    // Simple mock parsing logic
    sscanf(payload, "product: %s\nquantity: %d", dict.product, &dict.quantity);
    return dict;
}

void free_yaml_dict(yaml_dict dict) {
    free(dict.product);
}

// Mock function to simulate getting price for a product
double get_price_for_product_(const char *product) {
    if (strcmp(product, "default") == 0) {
        return 10.0;
    }
    return 0.0; // Unknown product
}

// Function to calculate the total price and return as YAML payload
char* calculate_price(const char *yaml_payload) {
    yaml_dict dict = parse_yaml(yaml_payload);
    double unit_price = get_price_for_product_(dict.product);
    double total_price = unit_price * dict.quantity;
    char *result = malloc(100); // Allocate enough space for the result
    sprintf(result, "total_price: %.2f", total_price);
    free_yaml_dict(dict);
    return result;
}

int main() {
    const char *yaml_payload = "product: default\nquantity: 3";
    char *result = calculate_price(yaml_payload);
    printf("%s\n", result);
    free(result); // Free the allocated memory
    return 0;
}