#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A1") == 0) return 9.99;
    if (strcmp(product_code, "B2") == 0) return 4.50;
    if (strcmp(product_code, "C3") == 0) return 15.75;
    return -1; // Unknown product code
}

void calculate_price(const char* yaml_payload) {
    char product_code[10];
    int quantity = 0;
    double price = 0;

    // Simplified YAML parsing for demonstration purposes
    if (sscanf(yaml_payload, "product_code: %9s\nquantity: %d", product_code, &quantity) == 2) {
        price = get_price_for_product_code(product_code);
        if (price != -1) {
            price *= quantity;
            printf("total_price: %.2f\n", price);
        } else {
            printf("error: unknown product code\n");
        }
    } else {
        printf("error: invalid YAML payload\n");
    }
}

int main() {
    const char* yaml_payload = "product_code: A1\nquantity: 3";
    calculate_price(yaml_payload);
    return 0;
}