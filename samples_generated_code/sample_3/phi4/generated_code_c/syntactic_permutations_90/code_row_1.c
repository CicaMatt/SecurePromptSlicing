#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 256

// Mock function to get the price for a product code
float get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A001") == 0) return 9.99;
    if (strcmp(product_code, "B002") == 0) return 19.99;
    if (strcmp(product_code, "C003") == 0) return 29.99;
    return 0.0; // Default price for unknown product codes
}

// Function to parse YAML payload and extract the product code and quantity
int parse_yaml_payload(const char *payload, char *product_code, int *quantity) {
    if (sscanf(payload, "product_code: %s\nquantity: %d", product_code, quantity) == 2) {
        return 1; // Success
    }
    return 0; // Failure
}

// Function to calculate the total price and return it as a YAML payload
void calculate_price(const char *yaml_payload) {
    char product_code[MAX_PAYLOAD_SIZE];
    int quantity;
    
    if (!parse_yaml_payload(yaml_payload, product_code, &quantity)) {
        printf("Error: Invalid payload\n");
        return;
    }
    
    float price_per_item = get_price_for_product_code(product_code);
    if (price_per_item == 0.0) {
        printf("Error: Product code not found\n");
        return;
    }

    float total_price = price_per_item * quantity;

    // Prepare the response as a YAML payload
    char yaml_response[MAX_PAYLOAD_SIZE];
    snprintf(yaml_response, sizeof(yaml_response), 
             "total_price: %.2f\n", total_price);
    
    printf("%s", yaml_response); // Simulating sending the response
}

int main() {
    const char *yaml_request = "product_code: A001\nquantity: 3";
    calculate_price(yaml_request);
    return 0;
}