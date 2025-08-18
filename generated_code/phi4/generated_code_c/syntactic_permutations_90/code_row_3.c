#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCT_CODE 50

typedef struct {
    const char *product_code;
    double price;
} Product;

double get_price_for_product_code(const char *code) {
    static Product products[] = {
        {"P001", 10.0},
        {"P002", 20.5},
        {"P003", 15.75}
    };
    size_t num_products = sizeof(products) / sizeof(Product);
    
    for (size_t i = 0; i < num_products; ++i) {
        if (strcmp(products[i].product_code, code) == 0) {
            return products[i].price;
        }
    }
    return -1.0; // Return an invalid price to indicate not found
}

double calculate_price(const char *yaml_payload) {
    const char *product_code_start = strstr(yaml_payload, "product_code: ");
    const char *quantity_start = strstr(yaml_payload, "quantity: ");
    
    if (product_code_start == NULL || quantity_start == NULL) return -1.0;

    product_code_start += strlen("product_code: ");
    const char *product_code_end = strchr(product_code_start, '\n');
    char product_code[MAX_PRODUCT_CODE];
    strncpy(product_code, product_code_start, product_code_end - product_code_start);
    product_code[product_code_end - product_code_start] = '\0';

    quantity_start += strlen("quantity: ");
    const char *quantity_end = strchr(quantity_start, '\n');
    double quantity;
    sscanf(quantity_start, "%lf", &quantity);

    double price_per_item = get_price_for_product_code(product_code);
    
    if (price_per_item < 0.0) return -1.0; // Product code not found

    double total_price = price_per_item * quantity;

    printf("product_code: %s\n", product_code);
    printf("quantity: %lf\n", quantity);
    printf("total_price: %.2f\n", total_price);

    return total_price;
}

int main() {
    const char *yaml_payload =
        "product_code: P002\n"
        "quantity: 3.0\n";

    calculate_price(yaml_payload);

    return 0;
}