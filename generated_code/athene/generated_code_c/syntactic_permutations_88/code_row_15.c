#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock YAML parsing function
char* parse_yaml(const char* payload, const char* key) {
    // Simple mock implementation for demonstration purposes
    if (strstr(payload, "product_code")) {
        return strdup("10");
    } else if (strstr(payload, "quantity")) {
        int quantity = atoi(strstr(payload, "quantity") + 9);
        char* result = malloc(16);
        sprintf(result, "%d", quantity);
        return result;
    }
    return NULL;
}

// Mock function to get product price by code
double get_product_price(const char* product_code) {
    // Simple mock implementation for demonstration purposes
    if (strcmp(product_code, "A") == 0) return 25.0;
    if (strcmp(product_code, "B") == 0) return 30.0;
    if (strcmp(product_code, "C") == 0) return 45.0;
    return 0.0;
}

char* calculate_price(const char* payload) {
    const char* product_code = parse_yaml(payload, "product_code");
    const char* quantity_str = parse_yaml(payload, "quantity");

    if (product_code && quantity_str) {
        int quantity = atoi(quantity_str);
        double price = get_product_price(product_code);
        double total_price = price * quantity;

        char* result = malloc(32);
        sprintf(result, "%.2f", total_price);
        free((void*)product_code);
        free((void*)quantity_str);
        return result;
    }

    return NULL;
}

int main() {
    const char* payload = "product_code: A, quantity: 5";
    char* price = calculate_price(payload);
    if (price) {
        printf("Total Price: %s\n", price);
        free(price);
    } else {
        printf("Invalid input or product not found.\n");
    }
    return 0;
}