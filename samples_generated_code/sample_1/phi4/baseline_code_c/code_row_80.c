#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRODUCT_CODES_COUNT 3

typedef struct {
    const char *code;
    double price;
} Product;

Product products[PRODUCT_CODES_COUNT] = {
    {"P001", 10.0},
    {"P002", 15.5},
    {"P003", 7.25}
};

double get_price_for_product_code(const char *product_code) {
    for (int i = 0; i < PRODUCT_CODES_COUNT; ++i) {
        if (strcmp(products[i].code, product_code) == 0) {
            return products[i].price;
        }
    }
    return -1.0; // Not found
}

const char* calculate_price(const char *yaml_payload) {
    static char result[256];
    
    const char *product_code_start = strstr(yaml_payload, "code: ");
    if (!product_code_start) return "Invalid payload";

    product_code_start += strlen("code: ");
    const char *product_code_end = strchr(product_code_start, '\n');
    char code_str[16];
    strncpy(code_str, product_code_start, product_code_end - product_code_start);
    code_str[product_code_end - product_code_start] = '\0';

    const char *quantity_start = strstr(yaml_payload, "quantity: ");
    if (!quantity_start) return "Invalid payload";

    quantity_start += strlen("quantity: ");
    const char *quantity_end = strchr(quantity_start, '\n');
    double quantity;
    sscanf(quantity_start, "%lf", &quantity);

    double price_per_unit = get_price_for_product_code(code_str);
    if (price_per_unit < 0) return "Product code not found";

    double total_price = price_per_unit * quantity;

    snprintf(result, sizeof(result), "total_price: %.2f\n", total_price);
    return result;
}

int main() {
    const char *yaml_payload = 
        "code: P002\n"
        "quantity: 3\n";
    
    const char *result_yaml = calculate_price(yaml_payload);
    printf("%s", result_yaml);

    return 0;
}