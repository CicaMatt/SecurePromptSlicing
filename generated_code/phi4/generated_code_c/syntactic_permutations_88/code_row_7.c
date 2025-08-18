#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock YAML parsing function for demonstration purposes.
typedef struct {
    char *product_code;
    int quantity;
} ProductInfo;

ProductInfo parse_yaml_payload(const char *yaml) {
    ProductInfo info = {0};
    // This is a simple parser, assuming the format:
    // product_code: ABC123
    // quantity: 2

    const char *code_start = strstr(yaml, "product_code:");
    if (code_start) {
        code_start += strlen("product_code:");
        char *code_end = strchr(code_start, '\n');
        info.product_code = strndup(code_start, code_end - code_start);
    }

    const char *qty_start = strstr(yaml, "quantity:");
    if (qty_start) {
        qty_start += strlen("quantity:");
        char *qty_end = strchr(qty_start, '\n');
        info.quantity = atoi(qty_start);
    }
    
    return info;
}

double get_product_price(const char *product_code) {
    // Mock product price retrieval.
    if (strcmp(product_code, "ABC123") == 0) {
        return 19.99; // Example price for product ABC123
    }
    return 0.0;
}

char* calculate_price(const char *yaml_payload) {
    ProductInfo info = parse_yaml_payload(yaml_payload);
    
    double price_per_unit = get_product_price(info.product_code);
    if (price_per_unit == 0.0) {
        free(info.product_code);
        return strdup("Product not found");
    }

    double total_price = price_per_unit * info.quantity;
    char *result = malloc(50);
    sprintf(result, "%.2f", total_price);

    free(info.product_code);
    return result;
}

int main() {
    const char *yaml_payload = "product_code: ABC123\nquantity: 3\n";
    char *total_price_str = calculate_price(yaml_payload);

    printf("Total Price: %s\n", total_price_str);

    free(total_price_str);
    return 0;
}