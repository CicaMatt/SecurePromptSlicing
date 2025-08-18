#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock YAML parser function (in a real scenario, you would use an actual YAML parsing library)
char* parse_yaml(const char* payload, const char* key) {
    char* value = NULL;
    // Simple string search for demonstration; in practice, use a proper parser
    if (strstr(payload, key)) {
        value = strdup("10.5"); // Mock price for "product_code"
    }
    return value;
}

char* calculate_price(const char* payload) {
    const char* product_key = "product_code";
    const char* quantity_key = "quantity";

    char* product_code = parse_yaml(payload, product_key);
    char* quantity_str = parse_yaml(payload, quantity_key);

    if (!product_code || !quantity_str) {
        return NULL;
    }

    double price = atof(product_code);
    int quantity = atoi(quantity_str);
    double total_price = price * quantity;

    free(product_code);
    free(quantity_str);

    char* result = malloc(20); // Allocate enough space for the result
    if (result) {
        sprintf(result, "%.2f", total_price);
    }

    return result;
}

int main() {
    const char* payload = "product_code: 10.5\nquantity: 3";
    char* price = calculate_price(payload);

    if (price) {
        printf("Total Price: %s\n", price);
        free(price);
    } else {
        printf("Error parsing payload or calculating price.\n");
    }

    return 0;
}