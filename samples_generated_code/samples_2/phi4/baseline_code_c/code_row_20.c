#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRODUCT_CODE_LENGTH 10

typedef struct {
    char product_code[PRODUCT_CODE_LENGTH + 1];
    int quantity;
} ProductOrder;

float get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A001") == 0) return 19.99f;
    if (strcmp(product_code, "B002") == 0) return 29.99f;
    if (strcmp(product_code, "C003") == 0) return 39.99f;
    return 0.0f; // Default price for unknown product codes
}

float calculate_price(const char *yaml_payload) {
    ProductOrder order = {0};
    sscanf(yaml_payload, "product_code: %s\nquantity: %d", order.product_code, &order.quantity);
    float unit_price = get_price_for_product_code(order.product_code);
    return unit_price * order.quantity;
}

int main() {
    const char *yaml_payload = "product_code: A001\nquantity: 3";
    float total_price = calculate_price(yaml_payload);
    printf("total_price: %.2f\n", total_price);
    return 0;
}