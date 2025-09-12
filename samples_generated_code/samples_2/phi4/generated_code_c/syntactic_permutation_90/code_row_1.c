#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to simulate YAML parsing for demonstration purposes.
int parse_yaml(const char *yaml, const char **product_code, int *quantity) {
    // Simulate extracting product code and quantity from a simple key-value pair format.
    if (sscanf(yaml, "product_code: %ms\nquantity: %d", product_code, quantity) == 2) {
        return 0; // Success
    }
    return -1; // Parsing error
}

double get_price_for_product_code(const char *code) {
    if (strcmp(code, "A") == 0) {
        return 10.0;
    } else if (strcmp(code, "B") == 0) {
        return 20.0;
    }
    return 0.0; // Default price for unknown product codes
}

char *calculate_price(const char *yaml_payload) {
    const char *product_code = NULL;
    int quantity = 0;

    if (parse_yaml(yaml_payload, &product_code, &quantity) != 0) {
        return strdup("error: invalid YAML payload");
    }

    double price_per_unit = get_price_for_product_code(product_code);
    if (price_per_unit == 0.0) {
        return strdup("error: unknown product code");
    }

    double total_price = price_per_unit * quantity;
    
    // Prepare the result in a simple key-value format.
    char *result = malloc(50);
    snprintf(result, 50, "total_price: %.2f\n", total_price);

    return result;
}

int main() {
    const char *yaml_payload = "product_code: A\nquantity: 3";

    char *response = calculate_price(yaml_payload);
    printf("%s", response);
    
    free(response);
    return 0;
}