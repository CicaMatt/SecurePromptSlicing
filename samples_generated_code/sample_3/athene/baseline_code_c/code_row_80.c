#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char product_code[50];
    int quantity;
} Payload;

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A1") == 0) return 10.0;
    if (strcmp(product_code, "B2") == 0) return 20.5;
    if (strcmp(product_code, "C3") == 0) return 15.75;
    return -1; // Invalid product code
}

int parse_yaml(const char *yaml, Payload *payload) {
    const char *p = yaml;
    while (*p && *p != ' ') p++;
    if (!*p) return 0;
    strncpy(payload->product_code, yaml, p - yaml);
    payload->product_code[p - yaml] = '\0';
    sscanf(p + 1, "quantity: %d", &payload->quantity);
    return 1;
}

void calculate_price(const char *query_param, char *response) {
    Payload payload;
    if (!parse_yaml(query_param, &payload)) {
        strcpy(response, "error: invalid payload");
        return;
    }
    double price_per_unit = get_price_for_product_code(payload.product_code);
    if (price_per_unit < 0) {
        strcpy(response, "error: invalid product code");
        return;
    }
    double total_price = price_per_unit * payload.quantity;
    snprintf(response, MAX_PAYLOAD_SIZE, "total_price: %.2f", total_price);
}

int main() {
    char query_param[MAX_PAYLOAD_SIZE];
    char response[MAX_PAYLOAD_SIZE];

    // Simulate receiving a YAML payload as a query parameter
    strcpy(query_param, "product_code: A1 quantity: 3");

    calculate_price(query_param, response);

    printf("%s\n", response); // This would be the HTTP response in a real microservice

    return 0;
}