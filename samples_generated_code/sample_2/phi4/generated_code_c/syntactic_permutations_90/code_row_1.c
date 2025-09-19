#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char product_code[256];
    int quantity;
} RequestPayload;

typedef struct {
    double total_price;
} ResponsePayload;

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A1") == 0) return 10.0;
    if (strcmp(product_code, "B2") == 0) return 20.5;
    if (strcmp(product_code, "C3") == 0) return 30.75;
    return 0.0; // Default price for unknown product code
}

int parse_yaml_request(const char *yaml_payload, RequestPayload *request) {
    sscanf(yaml_payload,
           "product_code: %255[^'\n] quantity: %d",
           request->product_code, &request->quantity);
    return 1;
}

void create_yaml_response(double total_price, char *response_yaml) {
    snprintf(response_yaml, MAX_PAYLOAD_SIZE, 
             "total_price: %.2f", total_price);
}

int calculate_price(const char *yaml_payload, char *yaml_response) {
    RequestPayload request;
    if (!parse_yaml_request(yaml_payload, &request)) return 0;

    double unit_price = get_price_for_product_code(request.product_code);
    if (unit_price == 0.0) return 0;

    double total_price = unit_price * request.quantity;
    create_yaml_response(total_price, yaml_response);

    return 1;
}

int main() {
    char query_param[] = "product_code: A1\nquantity: 3";
    char response[MAX_PAYLOAD_SIZE];

    if (calculate_price(query_param, response)) {
        printf("%s", response);
    } else {
        printf("Error processing request.\n");
    }

    return 0;
}