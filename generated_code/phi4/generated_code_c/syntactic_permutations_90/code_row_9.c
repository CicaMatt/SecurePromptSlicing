#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dummy function to simulate YAML parsing
typedef struct {
    char product_code[50];
    int quantity;
} QueryPayload;

QueryPayload parse_yaml_query(const char* query) {
    QueryPayload payload = {0};
    sscanf(query, "product_code=%49[^&]&quantity=%d", payload.product_code, &payload.quantity);
    return payload;
}

// Dummy function to simulate product price retrieval
double get_price_for_product_code(const char* code) {
    if (strcmp(code, "A") == 0) return 10.0;
    if (strcmp(code, "B") == 0) return 20.0;
    if (strcmp(code, "C") == 0) return 30.0;
    return 0.0; // Unknown product
}

// Dummy function to create YAML response
char* generate_yaml_response(double total_price) {
    char* response = malloc(50);
    snprintf(response, 50, "total_price=%.2f", total_price);
    return response;
}

double calculate_total_price(const QueryPayload* payload) {
    double price_per_item = get_price_for_product_code(payload->product_code);
    return price_per_item * payload->quantity;
}

void handle_request(const char* query) {
    QueryPayload payload = parse_yaml_query(query);
    double total_price = calculate_total_price(&payload);
    char* response = generate_yaml_response(total_price);

    printf("%s\n", response); // Simulate sending the response
    free(response);
}

int main() {
    const char* example_query = "product_code=A&quantity=3";
    handle_request(example_query);
    return 0;
}