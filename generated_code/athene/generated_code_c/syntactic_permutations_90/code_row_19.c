#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *product_code;
    int quantity;
} Order;

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 19.99;
    if (strcmp(product_code, "B456") == 0) return 24.99;
    if (strcmp(product_code, "C789") == 0) return 14.99;
    return -1; // Invalid product code
}

char* calculate_price(const char *yaml_payload) {
    Order order = { .product_code = NULL, .quantity = 0 };
    char *token, *payload_copy = strdup(yaml_payload);
    double total_price;

    for (token = strtok(payload_copy, " \n"); token != NULL; token = strtok(NULL, " \n")) {
        if (strncmp(token, "product_code:", 13) == 0) {
            order.product_code = strdup(token + 14);
        } else if (strncmp(token, "quantity:", 9) == 0) {
            order.quantity = atoi(token + 10);
        }
    }

    free(payload_copy);

    if (order.product_code != NULL && order.quantity > 0) {
        double price_per_unit = get_price_for_product_code(order.product_code);
        total_price = price_per_unit * order.quantity;
    } else {
        total_price = -1; // Invalid input
    }

    char buffer[256];
    snprintf(buffer, sizeof(buffer), "total_price: %.2f\n", total_price);

    free(order.product_code);

    return strdup(buffer);
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 2";
    char *result = calculate_price(yaml_payload);
    printf("%s", result);
    free(result); // Free the allocated memory
    return 0;
}