#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock YAML parsing function (for demonstration purposes)
void parse_yaml(const char *yaml, int *product_price, int *quantity) {
    // Simulating parsing with hardcoded values for the example
    if (strcmp(yaml, "price: 100\nquantity: 2") == 0) {
        *product_price = 100;
        *quantity = 2;
    } else {
        fprintf(stderr, "Invalid YAML format.\n");
        exit(EXIT_FAILURE);
    }
}

const char* calculate_price(const char *yaml_payload) {
    int product_price = 0;
    int quantity = 0;

    // Parse the YAML payload
    parse_yaml(yaml_payload, &product_price, &quantity);

    // Calculate total price
    int total_price = product_price * quantity;

    // Convert total price to string
    static char result[20];
    snprintf(result, sizeof(result), "%d", total_price);
    
    return result;
}

int main() {
    const char *yaml_payload = "price: 100\nquantity: 2";
    printf("Total Price: %s\n", calculate_price(yaml_payload));
    return 0;
}