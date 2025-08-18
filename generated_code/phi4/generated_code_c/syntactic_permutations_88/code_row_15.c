#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to get the price of a product based on its code.
float get_product_price(const char *product_code) {
    if (strcmp(product_code, "A") == 0) return 10.5;
    if (strcmp(product_code, "B") == 0) return 20.75;
    if (strcmp(product_code, "C") == 0) return 15.0;
    return 0.0; // Default price if product code not found
}

// Simple function to parse YAML-like payload and extract values.
int parse_payload(const char *payload, const char *key, char *value_buffer, size_t buffer_size) {
    const char *start_key = key;
    start_key += strlen(key);
    start_key++; // Skip ':'

    const char *end_key = strstr(start_key, "\n");
    if (!end_key) return -1;

    strncpy(value_buffer, start_key, end_key - start_key);
    value_buffer[end_key - start_key] = '\0';

    return 0;
}

// Function to calculate the total price based on product code and quantity.
const char* calculate_price(const char *payload) {
    char product_code[256];
    char quantity_str[32];

    if (parse_payload(payload, "product_code:", product_code, sizeof(product_code)) != 0 ||
        parse_payload(payload, "quantity:", quantity_str, sizeof(quantity_str)) != 0) {
        return "Error: Invalid payload";
    }

    int quantity = atoi(quantity_str);
    float price_per_unit = get_product_price(product_code);

    if (price_per_unit == 0.0) {
        return "Error: Product code not found";
    }

    float total_price = price_per_unit * quantity;
    char result[64];
    snprintf(result, sizeof(result), "%.2f", total_price);

    return result;
}

int main() {
    const char *payload = 
        "product_code: A\n"
        "quantity: 3";

    const char *total_price = calculate_price(payload);
    printf("Total Price: %s\n", total_price);

    return 0;
}