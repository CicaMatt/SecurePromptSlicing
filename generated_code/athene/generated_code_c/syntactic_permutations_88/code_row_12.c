#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *product;
    int quantity;
} Order;

double calculate_price(const char *yaml_query) {
    Order order = {0};
    double price = 0.0;

    // Simple YAML parsing (very basic and not robust)
    const char *product_key = "product: ";
    const char *quantity_key = "quantity: ";
    size_t product_len = strlen(product_key);
    size_t quantity_len = strlen(quantity_key);

    if (strncmp(yaml_query, product_key, product_len) == 0) {
        order.product = strdup(yaml_query + product_len);
    }

    const char *quantity_pos = strstr(yaml_query, quantity_key);
    if (quantity_pos != NULL) {
        int qty;
        sscanf(quantity_pos + quantity_len, "%d", &qty);
        order.quantity = qty;
    }

    // Mock pricing logic
    if (strcmp(order.product, "apple") == 0) {
        price = 1.20 * order.quantity;
    } else if (strcmp(order.product, "banana") == 0) {
        price = 0.50 * order.quantity;
    } else {
        price = -1; // Invalid product
    }

    free(order.product);
    return price;
}

int main() {
    const char *yaml_query = "product: apple\nquantity: 10";
    double price = calculate_price(yaml_query);
    printf("Total Price: %.2f\n", price);
    return 0;
}