#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A") == 0) return 10.99;
    else if (strcmp(product_code, "B") == 0) return 5.49;
    else if (strcmp(product_code, "C") == 0) return 20.75;
    return 0.0;
}

void parse_yaml_payload(const char *payload, char *product_code, int *quantity) {
    sscanf(payload, "product_code: %s\nquantity: %d", product_code, quantity);
}

char* calculate_price(const char *yaml_payload) {
    static char response[MAX_PAYLOAD_SIZE];
    char product_code[10];
    int quantity;
    double price;

    parse_yaml_payload(yaml_payload, product_code, &quantity);

    price = get_price_for_product_code(product_code) * quantity;

    snprintf(response, MAX_PAYLOAD_SIZE, "total_price: %.2f\n", price);
    return response;
}

int main() {
    const char *yaml_query_param = "product_code: A\nquantity: 3";
    char *result = calculate_price(yaml_query_param);

    printf("%s", result);
    return 0;
}