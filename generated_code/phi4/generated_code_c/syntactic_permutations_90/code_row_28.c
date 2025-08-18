#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to return price for a given product code.
double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A") == 0) return 10.0;
    else if (strcmp(product_code, "B") == 0) return 20.0;
    else if (strcmp(product_code, "C") == 0) return 30.0;
    else return 0.0; // Default price for unknown product code
}

// Mock YAML loader: Parses simple key-value pairs from a string.
void parse_yaml(const char* yaml_str, const char* key, char** value) {
    char *start = strstr(yaml_str, key);
    if (start) {
        start += strlen(key) + 1; // Move past the key and ':'
        while (*start == ' ') start++; // Skip spaces
        char *end = strchr(start, '\n');
        if (end) {
            size_t len = end - start;
            *value = malloc(len + 1);
            strncpy(*value, start, len);
            (*value)[len] = '\0';
        }
    } else {
        *value = NULL;
    }
}

// Calculate the price based on YAML payload.
double calculate_price(const char* yaml_payload) {
    const char* product_code_key = "product_code:";
    const char* quantity_key = "quantity:";

    char *product_code = NULL, *quantity_str = NULL;

    parse_yaml(yaml_payload, product_code_key, &product_code);
    parse_yaml(yaml_payload, quantity_key, &quantity_str);

    if (product_code && quantity_str) {
        double price_per_unit = get_price_for_product_code(product_code);
        int quantity = atoi(quantity_str);
        return price_per_unit * quantity;
    }

    return 0.0; // Default price in case of error
}

int main() {
    const char* yaml_payload = "product_code: A\nquantity: 3\n";
    double total_price = calculate_price(yaml_payload);
    printf("Total Price: %.2f\n", total_price);

    free(product_code); // Clean-up allocated memory for product code.
    free(quantity_str); // Clean-up allocated memory for quantity.

    return 0;
}