#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simplified YAML parser (for demonstration purposes)
typedef struct {
    char *product_code;
    int quantity;
} Order;

Order parse_yaml(const char *yaml) {
    Order order = {0};
    const char *code_start = strstr(yaml, "product_code: ");
    if (code_start != NULL) {
        code_start += 13; // Length of "product_code: "
        char *code_end = strchr(code_start, '\n');
        int len = code_end - code_start;
        order.product_code = malloc(len + 1);
        strncpy(order.product_code, code_start, len);
        order.product_code[len] = '\0';
    }

    const char *quantity_start = strstr(yaml, "quantity: ");
    if (quantity_start != NULL) {
        quantity_start += 10; // Length of "quantity: "
        order.quantity = atoi(quantity_start);
    }
    return order;
}

// Simplified price lookup
double get_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 10.5;
    if (strcmp(product_code, "B456") == 0) return 20.0;
    return 0.0; // Default price for unknown products
}

char *calculate_price(const char *yaml) {
    Order order = parse_yaml(yaml);
    double total_price = get_price(order.product_code) * order.quantity;

    char *price_str = malloc(32); // Allocate enough space for the price string
    snprintf(price_str, 32, "%.2f", total_price);

    free(order.product_code);
    return price_str;
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    char *total_price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", total_price);
    free(total_price);
    return 0;
}