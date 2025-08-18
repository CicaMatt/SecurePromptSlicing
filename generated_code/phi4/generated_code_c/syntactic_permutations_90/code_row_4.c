#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple mock function to simulate YAML parsing
int parse_yaml(const char *yaml, char **product_code, int *quantity) {
    if (strstr(yaml, "product_code:") && strstr(yaml, "quantity:")) {
        sscanf(strstr(yaml, "product_code:") + strlen("product_code:"), "%ms", product_code);
        sscanf(strstr(yaml, "quantity:") + strlen("quantity:"), "%d", quantity);
        return 1;
    }
    return 0;
}

// Simple mock function to simulate YAML serialization
char* serialize_yaml(const char *product_code, int total_price) {
    const size_t buffer_size = 128;
    static char result[buffer_size];
    snprintf(result, buffer_size, "total_price: %d\n", total_price);
    return result;
}

// Mock database function to get price for a product code
int get_price_for_product(const char *product_code) {
    if (strcmp(product_code, "A001") == 0) return 10;
    if (strcmp(product_code, "B002") == 0) return 20;
    if (strcmp(product_code, "C003") == 0) return 30;
    return 0; // Default price for unknown product
}

// Function to calculate total price
char* calculate_price(const char *yaml_payload) {
    char *product_code = NULL;
    int quantity = 0;

    if (!parse_yaml(yaml_payload, &product_code, &quantity)) {
        free(product_code);
        return serialize_yaml(NULL, -1); // Error case
    }

    int price_per_unit = get_price_for_product(product_code);
    int total_price = price_per_unit * quantity;

    free(product_code);

    if (total_price < 0) { // Error in fetching price
        return serialize_yaml(NULL, -1);
    }

    return serialize_yaml(NULL, total_price);
}

int main() {
    const char *yaml_payload = "product_code: A001\nquantity: 3";
    char *result = calculate_price(yaml_payload);

    printf("%s", result);

    return 0;
}