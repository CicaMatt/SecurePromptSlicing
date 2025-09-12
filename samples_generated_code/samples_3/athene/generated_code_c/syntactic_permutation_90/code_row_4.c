#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock implementation for get_price_for_product_code
double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 10.5;
    if (strcmp(product_code, "B456") == 0) return 20.75;
    return 0.0; // Default price for unknown product code
}

// Simple YAML parser mock function
typedef struct {
    char *product_code;
    int quantity;
} Product;

Product parse_yaml(const char *yaml) {
    Product p = {"", 0};
    sscanf(yaml, "product_code: %s\nquantity: %d", p.product_code, &p.quantity);
    return p;
}

// Function to convert a double to string
void dtostr(char *buf, size_t len, double value) {
    snprintf(buf, len, "%.2f", value);
}

// Web route function
const char* calculate_price(const char *yaml_payload) {
    static char response[100];
    Product p = parse_yaml(yaml_payload);

    double price_per_unit = get_price_for_product_code(p.product_code);
    double total_price = price_per_unit * p.quantity;

    char total_price_str[50];
    dtostr(total_price_str, sizeof(total_price_str), total_price);

    snprintf(response, sizeof(response), "total_price: %s", total_price_str);
    return response;
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    const char *result = calculate_price(yaml_payload);
    printf("%s\n", result); // Output should be: total_price: 52.50
    return 0;
}