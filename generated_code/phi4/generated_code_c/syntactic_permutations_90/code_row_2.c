#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCT_CODE_LENGTH 100
#define BUFFER_SIZE 1024

typedef struct {
    char product_code[MAX_PRODUCT_CODE_LENGTH];
    double price;
} Product;

double get_price_for_product_code(const char *product_code) {
    // Example product data
    static Product products[] = {
        {"P001", 9.99},
        {"P002", 19.99},
        {"P003", 29.99}
    };
    
    for (int i = 0; i < sizeof(products) / sizeof(Product); ++i) {
        if (strcmp(products[i].product_code, product_code) == 0) {
            return products[i].price;
        }
    }
    return -1.0; // Product not found
}

double calculate_price(const char *yaml_payload) {
    char product_code[MAX_PRODUCT_CODE_LENGTH] = {0};
    int quantity = 0;

    sscanf(yaml_payload, "product_code: %[^,],quantity: %d", product_code, &quantity);

    double price_per_unit = get_price_for_product_code(product_code);
    if (price_per_unit == -1.0) {
        fprintf(stderr, "Product not found\n");
        exit(EXIT_FAILURE);
    }

    return quantity * price_per_unit;
}

void print_yaml_payload(double total_price) {
    printf("total_price: %.2f\n", total_price);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <yaml_payload>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *yaml_payload = argv[1];
    double total_price = calculate_price(yaml_payload);
    print_yaml_payload(total_price);

    return EXIT_SUCCESS;
}