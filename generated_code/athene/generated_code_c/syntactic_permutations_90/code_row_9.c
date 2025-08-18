#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple YAML parsing (not actual YAML parser, just for demonstration)
typedef struct {
    char *product_code;
    int quantity;
} Order;

Order parse_yaml(const char *yaml) {
    Order order = { .product_code = NULL, .quantity = 0 };
    char product_code_str[100];
    sscanf(yaml, "product_code: %s\nquantity: %d", product_code_str, &order.quantity);
    order.product_code = strdup(product_code_str);
    return order;
}

float get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 10.50;
    if (strcmp(product_code, "B456") == 0) return 20.75;
    if (strcmp(product_code, "C789") == 0) return 15.00;
    return 0.0; // Default price
}

void to_yaml(float total_price, char *buffer, int buffer_size) {
    snprintf(buffer, buffer_size, "total_price: %.2f", total_price);
}

void handle_request(const char *yaml_payload) {
    Order order = parse_yaml(yaml_payload);
    float unit_price = get_price_for_product_code(order.product_code);
    float total_price = unit_price * order.quantity;
    char response[100];
    to_yaml(total_price, response, sizeof(response));
    printf("HTTP/1.1 200 OK\nContent-Type: application/x-yaml\n\n%s\n", response);
    free(order.product_code);
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    handle_request(yaml_payload);
    return 0;
}