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
    if (strcmp(product_code, "C789") == 0) return 15.75;
    return -1; // Invalid product code
}

char* calculate_price(const char *yaml_payload) {
    Order order = { .product_code = NULL, .quantity = 0 };
    char *token = strtok((char *)yaml_payload, ":\n ");
    while (token != NULL) {
        if (strcmp(token, "product_code") == 0) {
            token = strtok(NULL, ":\n ");
            order.product_code = strdup(token);
        } else if (strcmp(token, "quantity") == 0) {
            token = strtok(NULL, ":\n ");
            order.quantity = atoi(token);
        }
        token = strtok(NULL, ":\n ");
    }

    double total_price = get_price_for_product_code(order.product_code) * order.quantity;
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "total_price: %.2f\n", total_price);

    free(order.product_code);
    return strdup(buffer);
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    char *result = calculate_price(yaml_payload);
    printf("%s", result);
    free(result);
    return 0;
}