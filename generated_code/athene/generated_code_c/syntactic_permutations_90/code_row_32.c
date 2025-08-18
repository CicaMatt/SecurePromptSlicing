#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    const char *ptr = strstr(yaml_payload, "product_code:");
    if (ptr) {
        ptr += strlen("product_code: ");
        order.product_code = strdup(ptr);
        ptr = strchr(order.product_code, '\n');
        if (ptr) *ptr = '\0';
    }

    ptr = strstr(yaml_payload, "quantity:");
    if (ptr) {
        ptr += strlen("quantity: ");
        char quantity_str[10];
        strncpy(quantity_str, ptr, 9);
        quantity_str[9] = '\0';
        order.quantity = atoi(quantity_str);
    }

    double price_per_item = get_price_for_product_code(order.product_code);
    if (price_per_item < 0) {
        return strdup("total: -1");
    }

    double total_price = price_per_item * order.quantity;
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "total: %.2f", total_price);
    free(order.product_code);
    return strdup(buffer);
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    char *result = calculate_price(yaml_payload);
    printf("%s\n", result);
    free(result);
    return 0;
}