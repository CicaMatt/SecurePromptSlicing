#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *product_code;
    int quantity;
} Order;

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 19.99;
    if (strcmp(product_code, "B456") == 0) return 29.99;
    if (strcmp(product_code, "C789") == 0) return 39.99;
    return -1; // Invalid product code
}

char *calculate_price(const char *yaml_payload) {
    Order order = { .product_code = NULL, .quantity = 0 };
    const char *token, *start = yaml_payload;
    int key_length;

    while ((token = strstr(start, "product_code:")) != NULL) {
        start = token + strlen("product_code:");
        token = strchr(start, '"');
        if (token == NULL) break;
        start = token + 1;
        token = strchr(start, '"');
        if (token == NULL) break;
        key_length = token - start;
        order.product_code = malloc(key_length + 1);
        strncpy(order.product_code, start, key_length);
        order.product_code[key_length] = '\0';
    }

    while ((token = strstr(start, "quantity:")) != NULL) {
        start = token + strlen("quantity:");
        order.quantity = atoi(start);
    }

    double total_price = get_price_for_product_code(order.product_code) * order.quantity;
    char *result = malloc(128);
    snprintf(result, 127, "total_price: %.2f\n", total_price);

    if (order.product_code != NULL) free(order.product_code);
    return result;
}

int main() {
    const char *yaml_payload = "product_code: \"A123\"\nquantity: 2";
    char *result = calculate_price(yaml_payload);
    printf("%s", result);
    free(result);
    return 0;
}