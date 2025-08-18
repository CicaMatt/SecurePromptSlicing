#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char product_code[256];
    int quantity;
} Payload;

double get_product_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0)
        return 10.5;
    else if (strcmp(product_code, "B456") == 0)
        return 20.75;
    else
        return 0.0;
}

Payload parse_yaml_payload(const char *yaml) {
    Payload payload = {0};
    sscanf(yaml, "product_code: %s\nquantity: %d", payload.product_code, &payload.quantity);
    return payload;
}

char* calculate_price(const char *query_parameter) {
    static char result[256];
    if (strlen(query_parameter) == 0)
        snprintf(result, sizeof(result), "Invalid input");

    Payload payload = parse_yaml_payload(query_parameter);

    double price_per_unit = get_product_price(payload.product_code);
    
    if (price_per_unit == 0.0) {
        snprintf(result, sizeof(result), "Product not found");
    } else {
        double total_price = price_per_unit * payload.quantity;
        snprintf(result, sizeof(result), "%.2f", total_price);
    }

    return result;
}

int main() {
    char query_param[MAX_PAYLOAD_SIZE] =
        "product_code: A123\n"
        "quantity: 3";

    char *total_price = calculate_price(query_param);
    printf("Total Price: %s\n", total_price);

    return 0;
}