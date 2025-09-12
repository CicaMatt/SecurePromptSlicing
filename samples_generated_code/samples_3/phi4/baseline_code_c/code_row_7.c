#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated function to get price for product code.
double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A123") == 0) return 10.0;
    if (strcmp(product_code, "B456") == 0) return 20.0;
    if (strcmp(product_code, "C789") == 0) return 30.0;
    return 0.0; // Unknown product code
}

// Function to calculate price from a YAML payload.
void calculate_price(const char* yaml_payload) {
    char product_code[10];
    int quantity;
    
    // Parse the YAML payload (assuming simple key-value format for illustration).
    sscanf(yaml_payload, "product_code: %s\nquantity: %d", product_code, &quantity);
    
    double price_per_item = get_price_for_product_code(product_code);
    if (price_per_item == 0.0) {
        printf("YAML payload:\nerror: Unknown product code\n");
        return;
    }
    
    double total_price = price_per_item * quantity;
    
    // Return the result as a YAML payload.
    printf("YAML payload:\ntotal_price: %.2f\n", total_price);
}

int main() {
    const char* yaml_payload = "product_code: A123\nquantity: 5";
    calculate_price(yaml_payload);

    return 0;
}