#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *product_code;
    double price;
} Product;

double get_price_for_product_code(const char *code) {
    // Example product list
    Product products[] = {
        {"P001", 10.99},
        {"P002", 5.49},
        {"P003", 7.89}
    };
    size_t n = sizeof(products) / sizeof(products[0]);
    
    for (size_t i = 0; i < n; ++i) {
        if (strcmp(code, products[i].product_code) == 0) {
            return products[i].price;
        }
    }
    return -1.0; // Return an invalid price to indicate product not found
}

const char* calculate_price(const char *yaml_payload) {
    static char result[256];
    char code[16], quantity_str[16];

    // Extracting product_code and quantity from YAML payload
    sscanf(yaml_payload, "product_code: %s\nquantity: %s", code, quantity_str);

    double price = get_price_for_product_code(code);
    if (price == -1.0) {
        return "{}\n"; // Return empty YAML if product not found
    }

    int quantity = atoi(quantity_str);
    double total_price = price * quantity;

    snprintf(result, sizeof(result), "total_price: %.2f\n", total_price);

    return result;
}

int main() {
    const char *yaml_query = "product_code: P001\nquantity: 3";
    
    const char* yaml_response = calculate_price(yaml_query);
    printf("%s", yaml_response);

    return 0;
}