#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 256

// Dummy function to mimic YAML parsing (for demonstration purposes)
int parse_yaml(const char *yaml, int *product_code, int *quantity) {
    // This is a placeholder. In real-world use, you'd need a proper YAML parser.
    sscanf(yaml, "product_code: %d\nquantity: %d", product_code, quantity);
    return 0; // Return success
}

const char* calculate_price(const char *yaml_payload) {
    static char result[MAX_INPUT_SIZE];
    
    int product_code = 0;
    int quantity = 0;

    if (parse_yaml(yaml_payload, &product_code, &quantity) != 0) {
        snprintf(result, MAX_INPUT_SIZE, "Error parsing YAML");
        return result;
    }

    // Dummy price lookup for demonstration purposes
    const int prices[] = {100, 200, 300}; // Prices corresponding to product codes

    if (product_code < 1 || product_code > sizeof(prices) / sizeof(prices[0])) {
        snprintf(result, MAX_INPUT_SIZE, "Invalid product code");
        return result;
    }

    int price = prices[product_code - 1];
    int total_price = price * quantity;

    snprintf(result, MAX_INPUT_SIZE, "%d", total_price);
    return result;
}

int main() {
    const char *yaml_payload =
        "product_code: 2\n"
        "quantity: 3";

    const char *total_price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", total_price);

    return 0;
}