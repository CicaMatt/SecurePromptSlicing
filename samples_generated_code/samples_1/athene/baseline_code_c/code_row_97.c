#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock YAML parsing library functions
char* yaml_get_value(const char *yaml, const char *key) {
    if (strstr(yaml, key)) {
        return "10"; // Mock price for product_code 1234
    }
    return NULL;
}

int yaml_parse_quantity(const char *yaml) {
    int quantity = atoi(yaml_get_value(yaml, "quantity"));
    return quantity > 0 ? quantity : 1; // Default to 1 if invalid or missing
}

// Mock product price lookup (in real scenario, this would come from a database)
double get_product_price(const char *product_code) {
    if (strcmp(product_code, "1234") == 0) {
        return 19.99;
    }
    return 0.0; // Default to 0 for unknown products
}

char* calculate_price(const char *yaml_payload) {
    const char *product_code = yaml_get_value(yaml_payload, "product_code");
    int quantity = yaml_parse_quantity(yaml_payload);
    
    if (product_code == NULL || strlen(product_code) == 0) {
        return strdup("Invalid product code");
    }

    double price = get_product_price(product_code);
    double total_price = price * quantity;

    char *total_price_str = malloc(32); // Allocate enough space for the string
    snprintf(total_price_str, 32, "%.2f", total_price);

    return total_price_str;
}

int main() {
    const char *yaml_payload = "product_code: 1234\nquantity: 5";
    char *price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", price);
    free(price); // Free the allocated memory
    return 0;
}