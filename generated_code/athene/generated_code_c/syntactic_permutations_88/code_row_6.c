#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple YAML parser (for demonstration purposes only)
typedef struct {
    char *product_code;
    int quantity;
} Order;

Order parse_yaml(const char *yaml) {
    Order order = {0};
    const char *token, *value;
    token = strstr(yaml, "product_code:");
    if (token) {
        value = strchr(token, ':');
        if (value) {
            order.product_code = strdup(value + 1);
            while (*order.product_code && (*order.product_code == ' ' || *order.product_code == '\n')) {
                order.product_code++;
            }
        }
    }
    token = strstr(yaml, "quantity:");
    if (token) {
        value = strchr(token, ':');
        if (value) {
            sscanf(value + 1, "%d", &order.quantity);
        }
    }
    return order;
}

// Product price lookup
double get_product_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 5.99;
    if (strcmp(product_code, "B456") == 0) return 12.99;
    // Add more products as needed
    return -1; // Invalid product code
}

char *calculate_price(const char *yaml_payload) {
    Order order = parse_yaml(yaml_payload);
    double price = get_product_price(order.product_code);
    if (price < 0) {
        return strdup("Invalid product code");
    }
    double total_price = price * order.quantity;
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%.2f", total_price);
    free(order.product_code);
    return strdup(buffer);
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 2";
    char *total_price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", total_price);
    free(total_price);
    return 0;
}