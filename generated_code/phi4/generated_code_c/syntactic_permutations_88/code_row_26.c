#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

typedef struct {
    char product_code[50];
    int quantity;
} Product;

float get_product_price(const char *product_code) {
    if (strcmp(product_code, "P001") == 0) return 10.0f;
    if (strcmp(product_code, "P002") == 0) return 20.0f;
    if (strcmp(product_code, "P003") == 0) return 30.0f;
    return 0.0f; // Default price for unknown products
}

Product parse_yaml_payload(const char *payload) {
    Product product = { .quantity = 1 };
    sscanf(payload, "product_code: %s\nquantity: %d", product.product_code, &product.quantity);
    return product;
}

float calculate_price(const char *yaml_payload) {
    Product product = parse_yaml_payload(yaml_payload);
    float price_per_unit = get_product_price(product.product_code);
    if (price_per_unit == 0.0f) {
        fprintf(stderr, "Error: Unknown product code\n");
        exit(EXIT_FAILURE);
    }
    return price_per_unit * product.quantity;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <yaml_payload>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *yaml_payload = argv[1];
    float total_price = calculate_price(yaml_payload);
    printf("Total Price: %.2f\n", total_price);

    return 0;
}