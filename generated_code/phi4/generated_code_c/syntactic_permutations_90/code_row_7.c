#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate loading YAML payload into a dictionary.
typedef struct {
    char product_code[50];
    int quantity;
} ProductInfo;

ProductInfo parse_yaml_payload(const char *yaml) {
    ProductInfo info = {0};
    sscanf(yaml, "product_code: %49s\nquantity: %d", info.product_code, &info.quantity);
    return info;
}

// Mock function to simulate retrieving the price of a product by its code.
float get_product_price(const char *code) {
    if (strcmp(code, "ABC123") == 0) {
        return 19.99;
    }
    if (strcmp(code, "XYZ789") == 0) {
        return 29.99;
    }
    return 0.0; // Default price if product not found.
}

char* get_price_for_product_code(const char *yaml_payload) {
    ProductInfo info = parse_yaml_payload(yaml_payload);
    float unit_price = get_product_price(info.product_code);
    float total_price = unit_price * info.quantity;

    char response[256];
    snprintf(response, sizeof(response), "total_price: %.2f\n", total_price);

    return strdup(response); // Returning a dynamically allocated string.
}

int main() {
    const char *yaml_payload = "product_code: ABC123\nquantity: 3";
    char *response = get_price_for_product_code(yaml_payload);
    
    printf("%s", response);
    free(response); // Free the memory allocated by strdup.

    return 0;
}