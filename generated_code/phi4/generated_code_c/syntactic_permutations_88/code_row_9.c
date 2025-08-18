#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *product_code;
    int quantity;
} ProductInfo;

double get_product_price(const char *product_code) {
    if (strcmp(product_code, "ABC123") == 0) return 10.99;
    if (strcmp(product_code, "DEF456") == 0) return 15.49;
    // Add more product codes and prices as needed
    return 0.0; // Default price if not found
}

ProductInfo parse_yaml_payload(const char *yaml_payload) {
    ProductInfo info = {NULL, 0};
    const char *product_code_marker = "product_code: ";
    const char *quantity_marker = "quantity: ";

    const char *product_code_start = strstr(yaml_payload, product_code_marker);
    if (product_code_start) {
        product_code_start += strlen(product_code_marker);
        const char *product_code_end = strchr(product_code_start, '\n');
        size_t code_length = product_code_end ? (size_t)(product_code_end - product_code_start) : strlen(product_code_start);
        info.product_code = strndup(product_code_start, code_length);
    }

    const char *quantity_start = strstr(yaml_payload, quantity_marker);
    if (quantity_start) {
        quantity_start += strlen(quantity_marker);
        info.quantity = atoi(quantity_start);
    }

    return info;
}

char* calculate_price(const char *yaml_payload) {
    ProductInfo info = parse_yaml_payload(yaml_payload);

    if (!info.product_code || info.quantity <= 0) {
        return strdup("Invalid product code or quantity.");
    }

    double price_per_unit = get_product_price(info.product_code);
    double total_price = price_per_unit * info.quantity;

    char *result = (char *)malloc(50);
    snprintf(result, 50, "%.2f", total_price);

    free(info.product_code);
    return result;
}

int main() {
    const char *yaml_payload = "product_code: ABC123\nquantity: 3";
    char *total_price_str = calculate_price(yaml_payload);
    printf("Total Price: %s\n", total_price_str);
    free(total_price_str);
    return 0;
}