#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulate getting price for a given product code.
double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A001") == 0) return 10.0;
    if (strcmp(product_code, "B002") == 0) return 15.5;
    if (strcmp(product_code, "C003") == 0) return 7.25;
    return 0.0; // Default price for unknown product codes.
}

// Simulate a YAML parser function to extract values from YAML payload
typedef struct {
    char* product_code;
    int quantity;
} Payload;

Payload parse_yaml_payload(const char *yaml_payload) {
    Payload payload = { .product_code = NULL, .quantity = 0 };
    const char *start_key = "product_code: ";
    const char *end_key = "\n";
    const char *quantity_key = "quantity: ";

    // Find product code
    char *code_start = strstr(yaml_payload, start_key);
    if (code_start) {
        code_start += strlen(start_key);
        char *code_end = strchr(code_start, '\n');
        size_t len = code_end ? code_end - code_start : strlen(code_start);
        payload.product_code = malloc(len + 1);
        strncpy(payload.product_code, code_start, len);
        payload.product_code[len] = '\0';
    }

    // Find quantity
    char *quantity_start = strstr(yaml_payload, quantity_key);
    if (quantity_start) {
        quantity_start += strlen(quantity_key);
        payload.quantity = atoi(quantity_start);
    }

    return payload;
}

// Function to calculate price based on product code and quantity
double calculate_price(const char* yaml_payload) {
    Payload payload = parse_yaml_payload(yaml_payload);

    double unit_price = get_price_for_product_code(payload.product_code);
    free(payload.product_code);

    if (unit_price > 0 && payload.quantity > 0) {
        return unit_price * payload.quantity;
    }

    return 0.0; // Default total price for invalid input.
}

// Function to convert double to string
void double_to_string(double value, char* buffer, size_t max_buffer_size) {
    snprintf(buffer, max_buffer_size, "%.2f", value);
}

// Simulate a web route handler function that returns YAML payload
const char* handle_request(const char *yaml_payload) {
    static char response[256];
    double total_price = calculate_price(yaml_payload);

    // Create YAML response
    double_to_string(total_price, response, sizeof(response));
    snprintf(response, sizeof(response), "total_price: %.2f\n", total_price);
    
    return response;
}

int main() {
    const char *yaml_request = "product_code: A001\nquantity: 3";
    const char *response = handle_request(yaml_request);

    printf("%s", response); // Output should be the YAML payload with calculated total price.

    return 0;
}