#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple YAML parser (not fully compliant, just for demonstration)
typedef struct {
    char *product_code;
    int quantity;
} Order;

Order parse_yaml(const char *yaml) {
    Order order = {0};
    char product_code[100];
    int quantity;

    sscanf(yaml, "product_code: %s\nquantity: %d", product_code, &quantity);
    order.product_code = strdup(product_code);
    order.quantity = quantity;
    return order;
}

float get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 19.99;
    if (strcmp(product_code, "B456") == 0) return 29.99;
    if (strcmp(product_code, "C789") == 0) return 39.99;
    return 0.0;
}

char* calculate_price(const char *yaml_payload) {
    Order order = parse_yaml(yaml_payload);
    float price_per_unit = get_price_for_product_code(order.product_code);
    float total_price = price_per_unit * order.quantity;

    static char response[100];
    sprintf(response, "total_price: %.2f", total_price);

    free(order.product_code);
    return response;
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    char *result = calculate_price(yaml_payload);
    printf("%s\n", result);
    return 0;
}