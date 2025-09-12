#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *product_code;
    int quantity;
} ProductRequest;

typedef struct {
    double total_price;
} PriceResponse;

double get_price_for_product_code(const char *code) {
    if (strcmp(code, "A") == 0)
        return 10.0;
    else if (strcmp(code, "B") == 0)
        return 20.0;
    else
        return 0.0;
}

ProductRequest parse_yaml_payload(const char *yaml) {
    ProductRequest request;
    sscanf(yaml, "product_code: %ms\nquantity: %d", &request.product_code, &request.quantity);
    return request;
}

char* generate_yaml_response(double total_price) {
    static char response[50];
    snprintf(response, sizeof(response), "total_price: %.2f\n", total_price);
    return response;
}

void calculate_price(const char *yaml_payload) {
    ProductRequest request = parse_yaml_payload(yaml_payload);
    double price_per_unit = get_price_for_product_code(request.product_code);
    if (price_per_unit == 0.0) {
        printf("product_code: not_found\n");
        return;
    }
    
    double total_price = price_per_unit * request.quantity;
    char *response = generate_yaml_response(total_price);
    printf("%s", response);
}

int main() {
    const char *yaml_payload = "product_code: A\nquantity: 3";
    calculate_price(yaml_payload);

    return 0;
}