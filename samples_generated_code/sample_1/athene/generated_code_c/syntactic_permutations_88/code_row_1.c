#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple YAML parsing structure
typedef struct {
    char product_code[50];
    int quantity;
} Product;

// Mock function to get price by product code
double get_price_by_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 10.0;
    if (strcmp(product_code, "B456") == 0) return 20.0;
    return 0.0; // Default price
}

// Function to parse YAML payload and extract product_code and quantity
int parse_yaml(const char *yaml, Product *product) {
    const char *pc = strstr(yaml, "product_code:");
    const char *qty = strstr(yaml, "quantity:");

    if (pc && qty) {
        sscanf(pc + 12, "%s", product->product_code);
        sscanf(qty + 9, "%d", &product->quantity);
        return 1;
    }
    return 0;
}

// Entry point for the API
char *calculate_price(const char *yaml_payload) {
    Product product;
    if (!parse_yaml(yaml_payload, &product)) {
        return NULL; // Invalid YAML payload
    }

    double price = get_price_by_code(product.product_code);
    double total_price = price * product.quantity;

    char *total_price_str = malloc(20);
    sprintf(total_price_str, "%.2f", total_price);

    return total_price_str;
}

// Example usage
int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    char *price = calculate_price(yaml_payload);
    if (price) {
        printf("Total Price: %s\n", price);
        free(price);
    } else {
        printf("Invalid payload\n");
    }
    return 0;
}