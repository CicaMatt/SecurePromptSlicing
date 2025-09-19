#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char product_code[50];
    int quantity;
} QueryPayload;

typedef struct {
    double total_price;
} ResponsePayload;

double get_price_for_product_code(const char* code) {
    if (strcmp(code, "A001") == 0) return 10.5;
    if (strcmp(code, "B002") == 0) return 20.75;
    if (strcmp(code, "C003") == 0) return 15.0;
    return 0.0; // Default price for unknown product codes
}

void calculate_price(const char* yaml_query, char* yaml_response) {
    QueryPayload query = { .product_code = "", .quantity = 0 };
    ResponsePayload response;

    sscanf(yaml_query, "product_code: %49s\nquantity: %d", query.product_code, &query.quantity);
    
    double price_per_item = get_price_for_product_code(query.product_code);
    if (price_per_item == 0.0) {
        snprintf(yaml_response, 100, "total_price: null");
    } else {
        response.total_price = price_per_item * query.quantity;
        snprintf(yaml_response, 100, "total_price: %.2f", response.total_price);
    }
}

int main() {
    const char* yaml_query = "product_code: A001\nquantity: 3";
    char yaml_response[100];

    calculate_price(yaml_query, yaml_response);

    printf("%s\n", yaml_response);
    return 0;
}