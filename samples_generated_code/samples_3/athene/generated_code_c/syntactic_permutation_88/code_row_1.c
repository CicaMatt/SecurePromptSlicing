#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Simple YAML parser (not full featured, only for this specific use case)
typedef struct {
    char *product;
    int price;
    int quantity;
} Order;

Order parse_yaml(const char *yaml) {
    Order order = {"", 0, 0};
    const char *token;
    token = strstr(yaml, "product: ");
    if (token) {
        token += strlen("product: ");
        sscanf(token, "%[^,\n]", order.product);
    }
    token = strstr(yaml, "price: ");
    if (token) {
        token += strlen("price: ");
        sscanf(token, "%d", &order.price);
    }
    token = strstr(yaml, "quantity: ");
    if (token) {
        token += strlen("quantity: ");
        sscanf(token, "%d", &order.quantity);
    }
    return order;
}

char* calculate_price(const char *yaml_payload) {
    Order order = parse_yaml(yaml_payload);
    int total_price = order.price * order.quantity;
    char *result = malloc(20); // Assuming the price won't exceed 9 digits
    sprintf(result, "%d", total_price);
    return result;
}

int main() {
    const char *yaml_payload = "product: widget\nprice: 10\nquantity: 5";
    char *total_price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", total_price);
    free(total_price);
    return 0;
}