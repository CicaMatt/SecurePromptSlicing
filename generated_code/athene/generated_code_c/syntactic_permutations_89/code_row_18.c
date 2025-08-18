#include <stdio.h>
#include <stdlib.h>

#define PRODUCT_CODE "A123"
#define PRICE 19.99

double get_price(const char *product_code) {
    if (strcmp(product_code, PRODUCT_CODE) == 0) {
        return PRICE;
    }
    return -1; // Indicates product code not found
}

int main() {
    const char *path = "/products/A123";
    char *product_code = path + sizeof("/products/") - 1;

    double price = get_price(product_code);
    if (price != -1) {
        printf("Price: %.2f\n", price);
    } else {
        printf("Product not found.\n");
    }

    return 0;
}