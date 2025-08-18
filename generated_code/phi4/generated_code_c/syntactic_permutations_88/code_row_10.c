#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char product_code[32];
    int quantity;
} Product;

float get_product_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 10.99;
    if (strcmp(product_code, "B456") == 0) return 5.49;
    if (strcmp(product_code, "C789") == 0) return 7.89;
    return 0.0; // Default price for unknown products
}

Product parse_yaml_payload(const char *payload) {
    Product product = { .quantity = 1 };
    sscanf(payload, "product_code: %31s\nquantity: %d", 
           product.product_code, &product.quantity);
    return product;
}

char* calculate_price(const char *yaml_payload) {
    static char result[64];
    Product product = parse_yaml_payload(yaml_payload);
    float price = get_product_price(product.product_code);
    if (price == 0.0) {
        snprintf(result, sizeof(result), "Invalid product code");
    } else {
        float total_price = price * product.quantity;
        snprintf(result, sizeof(result), "%.2f", total_price);
    }
    return result;
}

int main() {
    const char *yaml_payload = 
        "product_code: A123\n"
        "quantity: 3";
    
    printf("Total Price: %s\n", calculate_price(yaml_payload));
    return 0;
}