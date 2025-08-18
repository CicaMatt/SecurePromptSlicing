#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A1") == 0) return 9.99;
    if (strcmp(product_code, "B2") == 0) return 4.99;
    if (strcmp(product_code, "C3") == 0) return 19.99;
    return -1; // Product not found
}

double calculate_price(const char* query_params) {
    char product_code[10];
    int quantity = 0;

    sscanf(query_params, "product_code=%[^&]&quantity=%d", product_code, &quantity);

    double price_per_unit = get_price_for_product_code(product_code);
    if (price_per_unit == -1) return -1; // Product not found

    return price_per_unit * quantity;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"product_code=<code>&quantity=<num>\"\n", argv[0]);
        exit(1);
    }

    double total_price = calculate_price(argv[1]);
    if (total_price == -1) {
        printf("Product not found or invalid query parameters.\n");
    } else {
        printf("Total price: %.2f\n", total_price);
    }

    return 0;
}