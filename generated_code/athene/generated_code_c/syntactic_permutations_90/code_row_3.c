#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *product_code;
    int quantity;
} Order;

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 19.99;
    if (strcmp(product_code, "B456") == 0) return 29.99;
    if (strcmp(product_code, "C789") == 0) return 39.99;
    return -1.0; // Invalid product code
}

char *calculate_price(const char *yaml_payload) {
    Order order = {0};
    double total_price = 0.0;

    // Simple YAML parser for this example
    sscanf(yaml_payload, "product_code: %s\nquantity: %d", order.product_code, &order.quantity);

    double price_per_unit = get_price_for_product_code(order.product_code);
    if (price_per_unit < 0) {
        return strdup("Error: Invalid product code");
    }

    total_price = price_per_unit * order.quantity;

    char *response = malloc(128);
    snprintf(response, 128, "total_price: %.2f", total_price);

    free(order.product_code);
    return response;
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    char *result = calculate_price(yaml_payload);
    printf("%s\n", result);
    free(result);
    return 0;
}