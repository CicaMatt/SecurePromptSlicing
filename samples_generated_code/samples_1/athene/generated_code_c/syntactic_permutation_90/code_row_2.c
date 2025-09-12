#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *product_code;
    int quantity;
} Order;

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 10.5;
    if (strcmp(product_code, "B456") == 0) return 20.75;
    if (strcmp(product_code, "C789") == 0) return 5.25;
    return -1; // Invalid product code
}

char* calculate_price(const char *yaml_payload) {
    Order order = { .product_code = NULL, .quantity = 0 };
    char *token, *str = strdup(yaml_payload);
    const char *delim = "\n ";

    token = strtok(str, delim);
    while (token != NULL) {
        if (strncmp(token, "product_code:", 13) == 0) {
            order.product_code = strdup(token + 14);
        } else if (strncmp(token, "quantity:", 9) == 0) {
            order.quantity = atoi(token + 10);
        }
        token = strtok(NULL, delim);
    }

    double total_price = get_price_for_product_code(order.product_code) * order.quantity;

    static char response[100];
    snprintf(response, sizeof(response), "total_price: %.2f\n", total_price);

    free(str);
    if (order.product_code != NULL) free(order.product_code);

    return response;
}

int main() {
    const char *yaml_payload = "product_code: A123\nquantity: 5";
    printf("%s", calculate_price(yaml_payload));
    return 0;
}