#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple YAML parser (for demonstration purposes, not production-ready)
typedef struct {
    char* product_code;
    int quantity;
} Order;

Order parse_yaml(const char* yaml) {
    Order order = {0};
    const char* p = strstr(yaml, "product_code:");
    if (p) {
        sscanf(p + 13, "%s", order.product_code);
    }
    p = strstr(yaml, "quantity:");
    if (p) {
        sscanf(p + 10, "%d", &order.quantity);
    }
    return order;
}

// Function to calculate the price based on product code
double get_price(const char* product_code) {
    if (strcmp(product_code, "A") == 0) return 10.0;
    if (strcmp(product_code, "B") == 0) return 20.0;
    if (strcmp(product_code, "C") == 0) return 30.0;
    return 0.0; // Default price
}

// Entry point for the API
char* calculate_price(const char* query_param) {
    Order order = parse_yaml(query_param);
    double total_price = get_price(order.product_code) * order.quantity;

    static char result[50];
    sprintf(result, "%.2f", total_price);
    return result;
}

int main() {
    const char* yaml_payload = "product_code: A\nquantity: 3";
    char* price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", price);
    return 0;
}