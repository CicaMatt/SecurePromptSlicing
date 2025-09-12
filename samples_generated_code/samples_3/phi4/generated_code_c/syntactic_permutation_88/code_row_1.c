#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024

typedef struct {
    double price;
    int quantity;
} Product;

double calculate_price(const char *yaml_payload) {
    Product product = {0, 0};
    sscanf(yaml_payload, "price: %lf\nquantity: %d", &product.price, &product.quantity);
    return product.price * product.quantity;
}

void handle_request(const char *query_param) {
    double total_price = calculate_price(query_param);
    printf("Total Price: %.2f\n", total_price);
}

int main() {
    const char *yaml_payload = "price: 19.99\nquantity: 3";
    handle_request(yaml_payload);
    return 0;
}