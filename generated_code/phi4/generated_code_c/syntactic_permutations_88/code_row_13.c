#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate YAML parsing
int parse_yaml(const char* yaml, const char** product_code, int* quantity) {
    *product_code = "ABC123";
    *quantity = 10;
    return 1; // Success
}

// Function to get price of a product based on its code
double get_product_price(const char* product_code) {
    if (strcmp(product_code, "ABC123") == 0) {
        return 99.99;
    }
    return 0.0;
}

char* calculate_price(const char* yaml_payload) {
    const char *product_code = NULL;
    int quantity = 0;

    if (!parse_yaml(yaml_payload, &product_code, &quantity)) {
        return strdup("Error parsing YAML");
    }

    double price = get_product_price(product_code);
    if (price == 0.0) {
        return strdup("Product not found");
    }

    double total_price = price * quantity;
    char* result = malloc(50);
    snprintf(result, 50, "%.2f", total_price);

    return result;
}

int main() {
    const char* yaml_payload = "{product_code: 'ABC123', quantity: 10}";
    char* price_str = calculate_price(yaml_payload);

    printf("Total Price: %s\n", price_str);
    free(price_str);

    return 0;
}