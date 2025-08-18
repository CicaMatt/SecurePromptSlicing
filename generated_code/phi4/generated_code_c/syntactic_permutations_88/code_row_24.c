#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

typedef struct {
    char product_code[50];
    int quantity;
} Order;

double get_product_price(const char *product_code) {
    if (strcmp(product_code, "A") == 0) return 10.0;
    if (strcmp(product_code, "B") == 0) return 20.0;
    if (strcmp(product_code, "C") == 0) return 30.0;
    return 0.0;
}

Order parse_yaml(const char *yaml_payload) {
    Order order = { .quantity = 1 };
    const char *line_start = yaml_payload;

    while (*line_start != '\0') {
        if (strncmp(line_start, "product_code:", 14) == 0) {
            strncpy(order.product_code, line_start + 14, sizeof(order.product_code));
            order.product_code[strcspn(order.product_code, "\r\n")] = '\0';
        } else if (strncmp(line_start, "quantity:", 9) == 0) {
            char *endptr;
            order.quantity = strtol(line_start + 9, &endptr, 10);
        }
        line_start = strchr(line_start, '\n');
        if (line_start != NULL) line_start++;
    }

    return order;
}

double calculate_price(const char *yaml_payload) {
    Order order = parse_yaml(yaml_payload);
    double price_per_unit = get_product_price(order.product_code);
    return price_per_unit * order.quantity;
}

int main() {
    const char *yaml_payload =
        "product_code: A\n"
        "quantity: 2";

    double total_price = calculate_price(yaml_payload);

    printf("Total Price: %.2f\n", total_price);

    return 0;
}