#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *product_code;
    int quantity;
} Order;

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 19.99;
    if (strcmp(product_code, "B456") == 0) return 29.99;
    if (strcmp(product_code, "C789") == 0) return 39.99;
    return -1; // Invalid product code
}

char* calculate_price(const char *yaml_payload) {
    Order order = { .product_code = NULL, .quantity = 0 };
    char *token = strtok((char *)yaml_payload, " ");
    while (token != NULL) {
        if (strncmp(token, "product_code:", 13) == 0) {
            token += 13;
            order.product_code = strdup(token);
        } else if (strncmp(token, "quantity:", 9) == 0) {
            token += 9;
            order.quantity = atoi(token);
        }
        token = strtok(NULL, " ");
    }

    double price_per_unit = get_price_for_product_code(order.product_code);
    double total_price = price_per_unit * order.quantity;

    char *result = malloc(128);
    snprintf(result, 128, "total_price: %.2f", total_price);
    free(order.product_code);
    return result;
}

int main() {
    const char *yaml_payload = "product_code: A123 quantity: 5";
    char *result = calculate_price(yaml_payload);
    printf("%s\n", result);
    free(result);
    return 0;
}