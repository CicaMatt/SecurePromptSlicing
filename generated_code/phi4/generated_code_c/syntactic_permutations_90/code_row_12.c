#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *product_code;
    int quantity;
} Order;

typedef struct {
    const char *key;
    float value;
} Product;

float get_price_for_product_code(const char *code) {
    if (strcmp(code, "A") == 0) return 10.0f;
    if (strcmp(code, "B") == 0) return 15.0f;
    if (strcmp(code, "C") == 0) return 20.0f;
    return 0.0f; // Default price for unknown products
}

float calculate_total_price(const Order *order) {
    float price_per_unit = get_price_for_product_code(order->product_code);
    return price_per_unit * order->quantity;
}

Order parse_order_from_yaml(const char *yaml_payload) {
    Order order;
    const char *product_code_start = strstr(yaml_payload, "product_code: ") + strlen("product_code: ");
    const char *product_code_end = strchr(product_code_start, '\n');
    size_t code_len = product_code_end - product_code_start;

    order.product_code = malloc(code_len + 1);
    strncpy(order.product_code, product_code_start, code_len);
    order.product_code[code_len] = '\0';

    const char *quantity_start = strstr(yaml_payload, "quantity: ") + strlen("quantity: ");
    const char *quantity_end = strchr(quantity_start, '\n');
    int quantity = atoi(quantity_start);

    order.quantity = quantity;
    return order;
}

void generate_yaml_response(float total_price) {
    printf("---\ntotal_price: %f\n", total_price);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <yaml_payload>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *yaml_payload = argv[1];
    Order order = parse_order_from_yaml(yaml_payload);
    float total_price = calculate_total_price(&order);

    generate_yaml_response(total_price);

    free(order.product_code);
    return EXIT_SUCCESS;
}