#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate getting product price from database or configuration
float get_product_price(const char *product_code) {
    if (strcmp(product_code, "P001") == 0) return 10.99;
    else if (strcmp(product_code, "P002") == 0) return 5.49;
    else return 0.0; // Unknown product
}

// Mock YAML parsing function
int parse_yaml(const char *yaml_payload, const char **product_code, int *quantity) {
    char buffer[256];
    if (sscanf(yaml_payload, "product_code: %255s\nquantity: %d", buffer, quantity) == 2) {
        *product_code = strdup(buffer);
        return 1;
    }
    return 0;
}

// Mock function to simulate a simple HTTP request handling
void handle_request(const char *request) {
    const char *product_code = NULL;
    int quantity = 0;

    if (parse_yaml(request, &product_code, &quantity)) {
        float price = get_product_price(product_code);
        free((void *)product_code); // Free the strdup memory

        if (price > 0.0) {
            float total_price = price * quantity;
            printf("Total Price: %.2f\n", total_price);
        } else {
            printf("Product not found.\n");
        }
    } else {
        printf("Failed to parse YAML payload.\n");
    }
}

int main() {
    // Simulate receiving a request with a YAML payload
    const char *request = "product_code: P001\nquantity: 3";
    
    handle_request(request);

    return 0;
}