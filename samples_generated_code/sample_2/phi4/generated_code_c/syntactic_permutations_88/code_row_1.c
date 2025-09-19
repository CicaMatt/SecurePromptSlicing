#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate YAML parsing, typically you would use a library like libyaml or yaml-cpp.
void parse_yaml(const char *payload, const char **product_code, int *quantity) {
    // In a real implementation, use proper YAML parsing
    if (sscanf(payload, "product_code: %m[^,\n] , quantity: %d", product_code, quantity) == 2) {
        printf("Parsed successfully.\n");
    } else {
        fprintf(stderr, "Failed to parse payload\n");
        exit(1);
    }
}

// Mock function to simulate getting the price of a product code
double get_price(const char *product_code) {
    // In practice, this could be a database lookup or similar
    if (strcmp(product_code, "ABC123") == 0) {
        return 10.99;
    } else {
        fprintf(stderr, "Unknown product code\n");
        exit(1);
    }
}

char* calculate_price(const char *yaml_payload) {
    const char *product_code = NULL;
    int quantity = 0;

    parse_yaml(yaml_payload, &product_code, &quantity);

    double price = get_price(product_code);
    double total_price = price * quantity;

    // Allocate memory for the resulting string
    char *result = malloc(50); // Adjust size as necessary
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    snprintf(result, 50, "%.2f", total_price);

    return result;
}

int main() {
    const char *yaml_payload = "product_code: ABC123 , quantity: 3";

    // Call the calculate_price function
    char *total_price_str = calculate_price(yaml_payload);
    
    printf("Total Price: %s\n", total_price_str);

    free(total_price_str); // Free allocated memory

    return 0;
}