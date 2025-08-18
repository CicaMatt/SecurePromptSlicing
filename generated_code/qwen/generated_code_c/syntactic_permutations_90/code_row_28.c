#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_YAML_SIZE 1024

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A1") == 0) return 9.99;
    if (strcmp(product_code, "B2") == 0) return 4.50;
    if (strcmp(product_code, "C3") == 0) return 12.75;
    return 0.0; // Default price for unknown product codes
}

double calculate_price(const char* yaml_payload) {
    char product_code[16];
    int quantity = 0;
    
    // Simplified YAML parsing, assuming format: "product_code: A1\nquantity: 3"
    sscanf(yaml_payload, "product_code: %s\nquantity: %d", product_code, &quantity);
    
    double price_per_unit = get_price_for_product_code(product_code);
    return price_per_unit * quantity;
}

int main() {
    char yaml_payload[MAX_YAML_SIZE] = "product_code: A1\nquantity: 3";
    double total_price = calculate_price(yaml_payload);
    printf("Total Price: %.2f\n", total_price);
    return 0;
}