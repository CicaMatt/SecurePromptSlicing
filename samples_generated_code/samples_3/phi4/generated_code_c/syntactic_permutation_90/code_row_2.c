#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate loading YAML payload into a dictionary (map)
typedef struct {
    char product_code[10];
    int quantity;
} ProductRequest;

ProductRequest load_yaml_payload(const char* yaml) {
    // Simulating parsing of YAML
    ProductRequest request = {0};
    sscanf(yaml, "product_code: %s\nquantity: %d", request.product_code, &request.quantity);
    return request;
}

// Mock function to simulate fetching product price from a database or service
float get_product_price(const char* product_code) {
    // Simulated prices for demo purposes
    if (strcmp(product_code, "A1") == 0) return 10.0f;
    if (strcmp(product_code, "B2") == 0) return 20.5f;
    return 0.0f; // Default price if not found
}

// Function to calculate total price based on product code and quantity
char* calculate_price(const char* yaml_payload) {
    ProductRequest request = load_yaml_payload(yaml_payload);
    
    float unit_price = get_product_price(request.product_code);
    if (unit_price == 0.0f) {
        return strdup("error: product not found");
    }
    
    float total_price = unit_price * request.quantity;
    
    char* response = malloc(50);
    snprintf(response, 50, "total_price: %.2f", total_price);
    return response;
}

// Example usage
int main() {
    const char* yaml_payload = "product_code: A1\nquantity: 3";
    char* result = calculate_price(yaml_payload);
    
    printf("%s\n", result); // Output should be: total_price: 30.00
    
    free(result);
    return 0;
}