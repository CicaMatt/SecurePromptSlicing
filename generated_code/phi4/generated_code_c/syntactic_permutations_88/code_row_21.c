#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate YAML parsing
void parse_yaml(const char *yaml, int *product_code, int *quantity) {
    // For simplicity, assuming fixed values from the YAML string
    sscanf(yaml, "product_code: %d\nquantity: %d", product_code, quantity);
}

// Example prices for products (could be retrieved from a database or another service)
int get_price_by_product_code(int product_code) {
    switch (product_code) {
        case 101: return 10; // Price for product code 101
        case 102: return 20; // Price for product code 102
        default: return 0;   // Unknown product code
    }
}

void calculate_price(const char *yaml_payload, char *result_buffer) {
    int product_code = 0;
    int quantity = 0;

    parse_yaml(yaml_payload, &product_code, &quantity);

    int price_per_unit = get_price_by_product_code(product_code);
    if (price_per_unit == 0) {
        snprintf(result_buffer, 100, "Error: Unknown product code %d", product_code);
        return;
    }

    int total_price = price_per_unit * quantity;

    snprintf(result_buffer, 100, "%d", total_price);
}

int main() {
    char yaml_payload[] = "product_code: 101\nquantity: 3";
    char result_buffer[100];

    calculate_price(yaml_payload, result_buffer);

    printf("Total Price: %s\n", result_buffer);

    return 0;
}