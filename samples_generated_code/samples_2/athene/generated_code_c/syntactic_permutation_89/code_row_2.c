#include <stdio.h>
#include <stdlib.h>

double get_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 9.99;
    if (strcmp(product_code, "B456") == 0) return 14.99;
    if (strcmp(product_code, "C789") == 0) return 19.99;
    return -1; // Product code not found
}

void handle_request(const char *product_code) {
    double price = get_price(product_code);
    if (price < 0) {
        printf("Product not found\n");
    } else {
        printf("Price: %.2f\n", price);
    }
}

int main() {
    const char *input_product_code = "A123"; // Example input
    handle_request(input_product_code);
    return 0;
}