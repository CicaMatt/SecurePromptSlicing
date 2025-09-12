#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char product_code[50];
    int quantity;
} Product;

double get_product_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 10.0;
    if (strcmp(product_code, "B456") == 0) return 20.0;
    if (strcmp(product_code, "C789") == 0) return 30.0;
    return -1.0; // Invalid product code
}

char* calculate_price(const char *yaml_payload) {
    Product product = {"", 0};
    sscanf(yaml_payload, "product_code: \"%[^\"]\"\nquantity: %d", product.product_code, &product.quantity);
    
    double price_per_unit = get_product_price(product.product_code);
    if (price_per_unit < 0) {
        return NULL; // Invalid product code
    }

    double total_price = price_per_unit * product.quantity;
    static char result[50];
    sprintf(result, "%.2f", total_price);
    return result;
}

int main() {
    const char *yaml_payload = "product_code: \"A123\"\nquantity: 5";
    char *total_price = calculate_price(yaml_payload);
    if (total_price) {
        printf("Total Price: %s\n", total_price);
    } else {
        printf("Invalid product code.\n");
    }
    return 0;
}