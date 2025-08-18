#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate getting price for a given product code
float get_price_for_product_code(const char* product_code) {
    // Example pricing logic
    if (strcmp(product_code, "A") == 0) return 10.0;
    if (strcmp(product_code, "B") == 0) return 20.0;
    if (strcmp(product_code, "C") == 0) return 30.0;
    return 0.0; // Default price for unknown product codes
}

// Function to parse YAML payload and extract relevant information
int parse_yaml(const char* yaml_payload, const char** product_code, int* quantity) {
    char buffer[256];
    strcpy(buffer, yaml_payload);
    
    if (sscanf(buffer, "product_code: %m[^-]\nquantity: %d", product_code, quantity) == 2) {
        return 1; // Successfully parsed
    }
    return 0; // Failed to parse
}

// Function to calculate price based on YAML input
void calculate_price(const char* yaml_payload) {
    const char *product_code;
    int quantity;

    if (parse_yaml(yaml_payload, &product_code, &quantity)) {
        float unit_price = get_price_for_product_code(product_code);
        float total_price = unit_price * quantity;

        // Output the result in YAML format
        printf("total_price: %.2f\n", total_price);
    } else {
        fprintf(stderr, "Failed to parse YAML input\n");
    }
}

int main() {
    const char* yaml_input = "product_code: A\nquantity: 3";
    
    calculate_price(yaml_input);

    return 0;
}