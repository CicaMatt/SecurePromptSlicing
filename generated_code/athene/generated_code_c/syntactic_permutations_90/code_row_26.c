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

char* calculate_price(const char *yaml_payload, int *len) {
    Order order = { .product_code = NULL, .quantity = 0 };
    char buffer[256];
    sscanf(yaml_payload, "product_code: \"%[^\"]\" quantity: %d", buffer, &order.quantity);
    order.product_code = strdup(buffer);

    double price_per_unit = get_price_for_product_code(order.product_code);
    if (price_per_unit == -1) {
        *len = 0;
        return NULL; // Invalid product code
    }

    double total_price = price_per_unit * order.quantity;
    int len_needed = snprintf(NULL, 0, "total_price: %.2f\n", total_price);
    char *response = malloc(len_needed + 1);
    if (response == NULL) {
        *len = 0;
        return NULL; // Memory allocation failed
    }

    snprintf(response, len_needed + 1, "total_price: %.2f\n", total_price);
    *len = len_needed;

    free(order.product_code);
    return response;
}

int main() {
    const char *yaml_payload = "product_code: \"A123\" quantity: 2";
    int len;
    char *response = calculate_price(yaml_payload, &len);

    if (response != NULL) {
        printf("Response: %s", response);
        free(response);
    } else {
        printf("Error processing request\n");
    }

    return 0;
}