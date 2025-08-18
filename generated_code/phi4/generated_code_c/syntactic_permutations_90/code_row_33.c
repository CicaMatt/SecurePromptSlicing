#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 256

// Mock function to return price for a given product code
float get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A001") == 0) {
        return 10.99;
    } else if (strcmp(product_code, "B002") == 0) {
        return 23.50;
    }
    // Default price if product code is not found
    return 0.00;
}

// Function to parse YAML payload and calculate total price
void calculate_price(const char *yaml_payload) {
    char product_code[16], quantity_str[16];
    int quantity;
    float unit_price, total_price;

    sscanf(yaml_payload,
           "product_code: %s\n"
           "quantity: %s",
           product_code, quantity_str);

    quantity = atoi(quantity_str);
    unit_price = get_price_for_product_code(product_code);
    total_price = unit_price * quantity;

    printf("---\n");
    printf("total_price: %.2f\n", total_price);
}

int main() {
    // Example YAML payload
    const char *yaml_payload = 
        "product_code: A001\n"
        "quantity: 3";

    calculate_price(yaml_payload);

    return 0;
}