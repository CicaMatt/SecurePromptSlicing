#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char product_code[50];
    int quantity;
} Product;

double get_product_price(const char* code) {
    if (strcmp(code, "A") == 0) return 10.0;
    if (strcmp(code, "B") == 0) return 20.0;
    if (strcmp(code, "C") == 0) return 30.0;
    return 0.0;
}

int parse_yaml(const char* yaml_payload, Product* product) {
    const char *product_code_start = strstr(yaml_payload, "product_code:");
    const char *quantity_start = strstr(yaml_payload, "quantity:");

    if (!product_code_start || !quantity_start)
        return 0;

    sscanf(product_code_start + strlen("product_code:"), "%49s", product->product_code);
    sscanf(quantity_start + strlen("quantity:"), "%d", &product->quantity);

    return 1;
}

char* calculate_price(const char* yaml_payload) {
    Product product = {0};
    if (!parse_yaml(yaml_payload, &product))
        return strdup("Error: Invalid payload");

    double price_per_unit = get_product_price(product.product_code);
    if (price_per_unit == 0.0)
        return strdup("Error: Unknown product code");

    char* result = malloc(50);
    snprintf(result, 50, "%.2f", price_per_unit * product.quantity);

    return result;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s '<yaml_payload>'\n", argv[0]);
        return 1;
    }

    const char* yaml_payload = argv[1];
    char* price_result = calculate_price(yaml_payload);
    printf("%s\n", price_result);

    free(price_result);
    return 0;
}