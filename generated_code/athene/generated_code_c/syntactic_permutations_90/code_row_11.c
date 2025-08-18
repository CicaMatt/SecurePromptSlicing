#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char product_code[50];
    int quantity;
} Payload;

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 10.50;
    if (strcmp(product_code, "B456") == 0) return 20.75;
    if (strcmp(product_code, "C789") == 0) return 30.00;
    return -1; // Unknown product code
}

int parse_yaml_payload(const char *payload, Payload *out) {
    const char *product_code_key = "product_code: ";
    const char *quantity_key = "quantity: ";

    char *copy = strdup(payload);
    if (!copy) return 0;

    char *token = strtok(copy, "\n");
    while (token != NULL) {
        if (strncmp(token, product_code_key, strlen(product_code_key)) == 0) {
            strncpy(out->product_code, token + strlen(product_code_key), sizeof(out->product_code) - 1);
        } else if (strncmp(token, quantity_key, strlen(quantity_key)) == 0) {
            out->quantity = atoi(token + strlen(quantity_key));
        }
        token = strtok(NULL, "\n");
    }

    free(copy);

    return strlen(out->product_code) > 0 && out->quantity > 0;
}

void calculate_price() {
    char payload[MAX_PAYLOAD_SIZE] = "product_code: A123\nquantity: 5";
    Payload request;

    if (!parse_yaml_payload(payload, &request)) {
        printf("Invalid payload\n");
        return;
    }

    double price_per_unit = get_price_for_product_code(request.product_code);
    if (price_per_unit < 0) {
        printf("Unknown product code\n");
        return;
    }

    double total_price = price_per_unit * request.quantity;

    char response[MAX_PAYLOAD_SIZE];
    snprintf(response, sizeof(response), "total_price: %.2f", total_price);

    printf("%s\n", response);
}

int main() {
    calculate_price();
    return 0;
}