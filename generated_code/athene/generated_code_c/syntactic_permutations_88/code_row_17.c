#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char product_code[50];
    int quantity;
} Product;

char* calculate_price(const char* yaml_payload) {
    Product product = {"A", 0}; // Default values
    const char *product_prices[] = {"10.00", "20.00", "30.00"}; // Prices for products A, B, C

    char key[50], value[50];
    sscanf(yaml_payload, "%s: %[^,\n]", key, product.product_code);
    sscanf(yaml_payload + strlen(key) + 1, ", %s: %d", key, &product.quantity);

    double price = 0.0;
    if (strcmp(product.product_code, "A") == 0) {
        price = atof(product_prices[0]);
    } else if (strcmp(product.product_code, "B") == 0) {
        price = atof(product_prices[1]);
    } else if (strcmp(product.product_code, "C") == 0) {
        price = atof(product_prices[2]);
    }

    double total_price = price * product.quantity;
    char* result = malloc(20);
    sprintf(result, "%.2f", total_price);

    return result;
}

int main() {
    const char* yaml_payload = "product_code: A, quantity: 5";
    char* price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", price);
    free(price);
    return 0;
}