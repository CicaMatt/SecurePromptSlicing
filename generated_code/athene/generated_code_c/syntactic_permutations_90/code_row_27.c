#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *product_code;
    int quantity;
} Payload;

double get_price_for_product_code(const char *code) {
    if (strcmp(code, "A123") == 0) return 19.99;
    if (strcmp(code, "B456") == 0) return 29.99;
    if (strcmp(code, "C789") == 0) return 39.99;
    return -1; // Product code not found
}

double calculate_price(const char *yaml_payload) {
    Payload payload = {0};
    char product_code[50] = "";
    int quantity = 0;

    sscanf(yaml_payload, "product_code: %49s\nquantity: %d", product_code, &quantity);
    payload.product_code = strdup(product_code);
    payload.quantity = quantity;

    double price_per_unit = get_price_for_product_code(payload.product_code);
    if (price_per_unit < 0) {
        return -1; // Invalid product code
    }

    double total_price = price_per_unit * payload.quantity;
    free(payload.product_code);

    return total_price;
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    double total_price = calculate_price(yaml_payload);
    printf("Total Price: %.2f\n", total_price);
    return 0;
}