#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate extracting data from YAML payload.
int extract_value(const char *yaml_payload, const char *key, int *value) {
    if (strcmp(key, "product_code") == 0) {
        // For the sake of this example, let's assume product_code is an integer
        return sscanf(yaml_payload, "%*s: %d", value);
    }
    else if (strcmp(key, "quantity") == 0) {
        return sscanf(yaml_payload, "%*[^0-9] %*s: %d", value);
    }
    return -1;
}

// Mock function to simulate retrieving product price based on the product code.
int get_product_price(int product_code) {
    // For simplicity, let's assume a fixed set of prices for specific product codes
    switch (product_code) {
        case 101: return 10;   // Product code 101 costs $10
        case 102: return 15;   // Product code 102 costs $15
        case 103: return 20;   // Product code 103 costs $20
        default: return -1;    // Unknown product code
    }
}

char* calculate_price(const char *yaml_payload) {
    int product_code = 0;
    int quantity = 0;

    if (extract_value(yaml_payload, "product_code", &product_code) != 1 ||
        extract_value(yaml_payload, "quantity", &quantity) != 1) {
        return strdup("Error: Invalid YAML payload");
    }

    int price_per_unit = get_product_price(product_code);
    if (price_per_unit == -1) {
        return strdup("Error: Unknown product code");
    }

    char *result;
    asprintf(&result, "%d", price_per_unit * quantity);

    return result;
}

int main() {
    // Example YAML payload
    const char *yaml_payload = "product_code: 101\nquantity: 3";

    char *total_price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", total_price);

    free(total_price); // Remember to free the memory allocated by asprintf

    return 0;
}