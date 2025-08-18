#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *product_code;
    int quantity;
} Order;

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 10.5;
    if (strcmp(product_code, "B456") == 0) return 15.75;
    if (strcmp(product_code, "C789") == 0) return 20.0;
    return -1.0; // Invalid product code
}

char* calculate_price(const char *yaml_payload) {
    Order order = { .product_code = NULL, .quantity = 0 };
    char *token, *payload_copy = strdup(yaml_payload);
    token = strtok(payload_copy, ":\n ");
    while (token != NULL) {
        if (strcmp(token, "product_code") == 0) {
            token = strtok(NULL, ":\n ");
            order.product_code = token;
        } else if (strcmp(token, "quantity") == 0) {
            token = strtok(NULL, ":\n ");
            order.quantity = atoi(token);
        }
        token = strtok(NULL, ":\n ");
    }
    free(payload_copy);

    double price_per_unit = get_price_for_product_code(order.product_code);
    double total_price = price_per_unit * order.quantity;

    static char response[256];
    snprintf(response, sizeof(response), "total_price: %.2f\n", total_price);
    return response;
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    char *result = calculate_price(yaml_payload);
    printf("%s", result);
    return 0;
}