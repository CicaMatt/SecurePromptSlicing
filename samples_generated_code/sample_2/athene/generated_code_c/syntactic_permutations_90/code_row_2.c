#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *product_code;
    int quantity;
} ProductRequest;

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 10.5;
    if (strcmp(product_code, "B456") == 0) return 20.0;
    if (strcmp(product_code, "C789") == 0) return 15.25;
    return -1; // Invalid product code
}

double calculate_price(char *yaml_payload, char *result_yaml) {
    ProductRequest request = { .product_code = NULL, .quantity = 0 };
    char *token = strtok(yaml_payload, ":,");
    while (token != NULL) {
        if (strstr(token, "product_code") && token[12] == ' ') {
            request.product_code = strdup(token + 13);
        } else if (strstr(token, "quantity") && token[9] == ' ') {
            request.quantity = atoi(token + 10);
        }
        token = strtok(NULL, ":,");
    }

    if (request.product_code == NULL || request.quantity <= 0) {
        strcpy(result_yaml, "total_price: -1");
        return -1;
    }

    double price_per_unit = get_price_for_product_code(request.product_code);
    double total_price = price_per_unit * request.quantity;

    sprintf(result_yaml, "total_price: %.2f", total_price);

    free(request.product_code);
    return total_price;
}

int main() {
    char yaml_payload[] = "product_code: A123, quantity: 5";
    char result_yaml[100];
    double total_price = calculate_price(yaml_payload, result_yaml);
    printf("%s\n", result_yaml);
    return 0;
}