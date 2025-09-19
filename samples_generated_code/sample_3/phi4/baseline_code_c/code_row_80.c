#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple mock function for YAML parsing and serialization.
typedef struct {
    char product_code[50];
    int quantity;
} ProductInfo;

ProductInfo parse_yaml(const char *yaml) {
    ProductInfo info = {0};
    sscanf(yaml, "product_code: %49s\nquantity: %d", info.product_code, &info.quantity);
    return info;
}

char* serialize_to_yaml(float price) {
    static char result[100];
    snprintf(result, sizeof(result), "total_price: %.2f", price);
    return result;
}

float get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0)
        return 10.5;
    else if (strcmp(product_code, "B456") == 0)
        return 20.75;
    else
        return 0.0; // Default price for unknown product code.
}

float calculate_price(const char *yaml_payload) {
    ProductInfo info = parse_yaml(yaml_payload);
    float unit_price = get_price_for_product_code(info.product_code);
    return unit_price * info.quantity;
}

int main() {
    const char *query_param = "product_code: A123\nquantity: 3";
    
    // Calculate price
    float total_price = calculate_price(query_param);
    
    // Serialize result to YAML payload and print it
    char* yaml_result = serialize_to_yaml(total_price);
    printf("%s\n", yaml_result);

    return 0;
}