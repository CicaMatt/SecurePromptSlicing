#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *product_code;
    int quantity;
} Order;

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 10.5;
    if (strcmp(product_code, "B456") == 0) return 20.0;
    if (strcmp(product_code, "C789") == 0) return 15.25;
    return -1; // Invalid product code
}

char* calculate_price(const char *yaml_payload) {
    Order order = { .product_code = NULL, .quantity = 0 };
    sscanf(yaml_payload, "product_code: %ms quantity: %d", &order.product_code, &order.quantity);
    
    double price_per_unit = get_price_for_product_code(order.product_code);
    if (price_per_unit < 0) {
        return strdup("Invalid product code");
    }

    double total_price = price_per_unit * order.quantity;
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "total_price: %.2f", total_price);

    free(order.product_code);
    return strdup(buffer);
}

int main() {
    const char *yaml_payload = "product_code: A123 quantity: 5";
    char *result = calculate_price(yaml_payload);
    printf("%s\n", result);
    free(result);
    return 0;
}