#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate getting a price for a given product code.
float get_price_for_product_code(const char *product_code) {
    // In a real scenario, this would query a database or another service.
    if (strcmp(product_code, "PROD123") == 0) {
        return 10.99;
    } else if (strcmp(product_code, "PROD456") == 0) {
        return 20.49;
    }
    // Default price for unknown product codes
    return 0.0f;
}

// Function to simulate a web route that processes a YAML payload.
void calculate_price(const char *yaml_payload) {
    float total_price = 0.0f;

    // Parse the YAML payload manually (for simplicity, assume well-formed input)
    const char *product_code_start = strstr(yaml_payload, "product_code: ");
    const char *quantity_start = strstr(yaml_payload, "quantity: ");

    if (product_code_start && quantity_start) {
        product_code_start += strlen("product_code: ");
        int product_code_length = quantity_start - product_code_start;
        char product_code[256];
        strncpy(product_code, product_code_start, product_code_length);
        product_code[product_code_length] = '\0';

        quantity_start += strlen("quantity: ");
        float quantity = atof(quantity_start);

        total_price = get_price_for_product_code(product_code) * quantity;

        // Print the result as YAML payload
        printf("total_price: %f\n", total_price);
    } else {
        fprintf(stderr, "Invalid YAML payload\n");
    }
}

int main() {
    const char *yaml_payload = "product_code: PROD123\ncategory: electronics\nquantity: 2";
    
    calculate_price(yaml_payload);

    return 0;
}