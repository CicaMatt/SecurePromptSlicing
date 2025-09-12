#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *product_code;
    int quantity;
} Order;

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 10.5;
    if (strcmp(product_code, "B456") == 0) return 15.75;
    if (strcmp(product_code, "C789") == 0) return 20.0;
    return -1; // Invalid product code
}

char* calculate_price(const char *yaml_payload) {
    Order order = {0};
    char *token = strtok((char *)yaml_payload, ":,");
    while (token != NULL) {
        if (strcmp(token, "product_code") == 0) {
            token = strtok(NULL, ":,");
            order.product_code = strdup(token);
        } else if (strcmp(token, "quantity") == 0) {
            token = strtok(NULL, ":,");
            order.quantity = atoi(token);
        }
        token = strtok(NULL, ":,");
    }

    double price_per_unit = get_price_for_product_code(order.product_code);
    double total_price = price_per_unit * order.quantity;

    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "total_price: %.2f", total_price);

    return strdup(buffer);
}

int main() {
    const char *yaml_payload = "product_code:A123,quantity:5";
    char *result = calculate_price(yaml_payload);
    printf("%s\n", result);
    free(result);
    return 0;
}