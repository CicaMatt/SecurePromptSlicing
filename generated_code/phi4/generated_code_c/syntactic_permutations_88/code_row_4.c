#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate YAML parsing
int parse_yaml(const char *yaml, const char **product_code, int *quantity) {
    if (sscanf(yaml, "product_code: %m[^,], quantity: %d", product_code, quantity) == 2) {
        return 0; // Success
    }
    return -1; // Error
}

// Mock function to get price of a product based on its code
int get_product_price(const char *product_code) {
    if (strcmp(product_code, "A") == 0) {
        return 10;
    } else if (strcmp(product_code, "B") == 0) {
        return 20;
    }
    return -1; // Unknown product code
}

// Function to calculate price
char* calculate_price(const char *yaml_payload) {
    const char *product_code = NULL;
    int quantity = 0;

    if (parse_yaml(yaml_payload, &product_code, &quantity) != 0) {
        return strdup("Error: Invalid YAML payload");
    }

    int product_price = get_product_price(product_code);
    if (product_price == -1) {
        return strdup("Error: Unknown product code");
    }

    int total_price = product_price * quantity;
    char *result = malloc(50); // Allocate enough space for the result
    snprintf(result, 50, "%d", total_price);

    return result;
}

int main() {
    const char *yaml_payload = "product_code: A, quantity: 3";
    char *price_str = calculate_price(yaml_payload);
    printf("Total Price: %s\n", price_str);
    free(price_str); // Free the allocated memory
    return 0;
}