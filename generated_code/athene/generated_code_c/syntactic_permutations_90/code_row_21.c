#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *product_code;
    int quantity;
} Order;

typedef struct {
    double price;
} Response;

double get_price_for_product_code(const char *code) {
    if (strcmp(code, "A123") == 0) return 10.5;
    else if (strcmp(code, "B456") == 0) return 20.0;
    else if (strcmp(code, "C789") == 0) return 15.25;
    return -1; // Product not found
}

char *calculate_price(const char *yaml_payload) {
    Order order = { .product_code = NULL, .quantity = 0 };
    Response response = { .price = 0 };

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

    double unit_price = get_price_for_product_code(order.product_code);
    response.price = unit_price * order.quantity;

    char buffer[256];
    snprintf(buffer, sizeof(buffer), "price: %.2f\n", response.price);

    free(order.product_code);
    return strdup(buffer);
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 2";
    char *response = calculate_price(yaml_payload);
    printf("%s", response);
    free(response);
    return 0;
}