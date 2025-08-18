#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char product_code[50];
    int quantity;
} Product;

float get_product_price(const char *product_code) {
    if (strcmp(product_code, "A001") == 0) return 10.0f;
    if (strcmp(product_code, "B002") == 0) return 20.0f;
    if (strcmp(product_code, "C003") == 0) return 30.0f;
    return 0.0f; // Unknown product code
}

Product parse_yaml_payload(const char *payload) {
    Product product = {"", 0};
    sscanf(payload, "product_code: %49s\nquantity: %d", product.product_code, &product.quantity);
    return product;
}

char* calculate_price(const char *yaml_payload) {
    static char result[100];
    Product product = parse_yaml_payload(yaml_payload);
    float price_per_unit = get_product_price(product.product_code);
    if (price_per_unit == 0.0f) {
        strcpy(result, "Error: Unknown product code");
    } else {
        sprintf(result, "%.2f", price_per_unit * product.quantity);
    }
    return result;
}

int main() {
    const char *yaml_payload = 
        "product_code: A001\n"
        "quantity: 3";

    printf("Total Price: %s\n", calculate_price(yaml_payload));
    return 0;
}