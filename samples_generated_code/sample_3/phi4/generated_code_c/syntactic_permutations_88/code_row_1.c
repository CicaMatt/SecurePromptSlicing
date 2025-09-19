#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mocking YAML parsing function for demonstration purposes
typedef struct {
    char product_code[50];
    int quantity;
    double price;
} Product;

int parse_yaml(const char *yaml_data, Product *product) {
    if (sscanf(yaml_data, "product_code: %49s\nquantity: %d\nprice: %lf",
               product->product_code, &product->quantity, &product->price) == 3) {
        return 1; // Success
    }
    return 0; // Failure
}

const char* calculate_price(const char *yaml_payload) {
    static char total_price_str[50];
    
    Product product = { .quantity = 0, .price = 0.0 };
    
    if (!parse_yaml(yaml_payload, &product)) {
        return "Error: Invalid YAML payload";
    }
    
    double total_price = product.quantity * product.price;
    snprintf(total_price_str, sizeof(total_price_str), "%.2f", total_price);
    
    return total_price_str;
}

int main() {
    const char *yaml_input = 
        "product_code: widget\n"
        "quantity: 3\n"
        "price: 19.99";
        
    const char* result = calculate_price(yaml_input);
    printf("Total Price: %s\n", result);

    return 0;
}