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
    if (strcmp(product_code, "C789") == 0) return 15.25;
    return -1; // Invalid product code
}

double calculate_price(const char *yaml_payload) {
    Order order = {0};
    char product_code[32];
    int quantity;

    sscanf(yaml_payload, "product_code: \"%[^\"\n]\"\nquantity: %d", product_code, &quantity);
    order.product_code = strdup(product_code);
    order.quantity = quantity;

    double price_per_unit = get_price_for_product_code(order.product_code);
    if (price_per_unit < 0) {
        fprintf(stderr, "Invalid product code\n");
        free(order.product_code);
        return -1;
    }

    double total_price = price_per_unit * order.quantity;
    free(order.product_code);
    return total_price;
}

int main() {
    const char *yaml_payload = "product_code: \"A123\"\nquantity: 5";
    double total_price = calculate_price(yaml_payload);
    if (total_price >= 0) {
        printf("Total Price: %.2f\n", total_price);
    } else {
        printf("Error calculating price.\n");
    }
    return 0;
}