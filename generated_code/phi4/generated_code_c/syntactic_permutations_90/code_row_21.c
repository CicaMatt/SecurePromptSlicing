#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CODE_LEN 10

typedef struct {
    char product_code[MAX_CODE_LEN];
    int quantity;
} ProductRequest;

typedef struct {
    double total_price;
} PriceResponse;

double get_price_for_product_code(const char *code) {
    if (strcmp(code, "A123") == 0)
        return 12.50;
    if (strcmp(code, "B456") == 0)
        return 7.30;
    if (strcmp(code, "C789") == 0)
        return 5.99;

    return 0.0; // Default price for unknown product codes
}

void parse_yaml(const char *yaml_str, ProductRequest *request) {
    sscanf(yaml_str, "product_code: %s\nquantity: %d", request->product_code, &request->quantity);
}

void format_yaml_response(PriceResponse response, char *out_yaml, size_t out_size) {
    snprintf(out_yaml, out_size, "total_price: %.2f\n", response.total_price);
}

double calculate_price(const char *yaml_payload) {
    ProductRequest request;
    parse_yaml(yaml_payload, &request);

    double unit_price = get_price_for_product_code(request.product_code);
    if (unit_price == 0.0) {
        return -1; // Error: Unknown product code
    }

    return unit_price * request.quantity;
}

void handle_web_request(const char *yaml_query_param) {
    double total_price = calculate_price(yaml_query_param);

    if (total_price < 0) {
        printf("Error: Invalid product code\n");
        return;
    }

    PriceResponse response = { .total_price = total_price };
    char yaml_response[256];
    format_yaml_response(response, yaml_response, sizeof(yaml_response));

    printf("%s", yaml_response);
}

int main() {
    const char *yaml_query_param = "product_code: A123\nquantity: 3";
    handle_web_request(yaml_query_param);

    return 0;
}