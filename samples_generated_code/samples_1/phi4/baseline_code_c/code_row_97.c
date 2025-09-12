#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YAML_BUFFER_SIZE 1024

// Mock function to simulate getting query parameter from a request
char* get_query_param(const char *key) {
    // In a real implementation, this would extract the actual query parameter value.
    if (strcmp(key, "payload") == 0) {
        return "{product_code: '123', quantity: 2}\n";
    }
    return NULL;
}

// Mock function to simulate parsing YAML in C
int parse_yaml(const char *yaml_str, const char **key, const char **value) {
    // A simple parser for demonstration purposes only.
    const char *start = strstr(yaml_str, key[0]);
    if (start) {
        start += strlen(key[0]) + 3; // Skip "key: "
        const char *end = strchr(start, '\n');
        if (end) {
            size_t len = end - start;
            char *val = (char *)malloc(len + 1);
            strncpy(val, start, len);
            val[len] = '\0';
            *value = val;
            return 1; // Success
        }
    }
    return 0; // Failure
}

// Mock function to get product price from a database or similar source
double get_product_price(const char *product_code) {
    if (strcmp(product_code, "123") == 0) {
        return 10.50;
    }
    return 0.0;
}

const char* calculate_price() {
    static char result[64];
    
    const char *yaml_payload = get_query_param("payload");
    if (!yaml_payload) {
        snprintf(result, sizeof(result), "Error: No payload provided.");
        return result;
    }

    const char *product_code_value = NULL;
    const char *quantity_value = NULL;

    // Parse the YAML payload
    parse_yaml(yaml_payload, "product_code", &product_code_value);
    parse_yaml(yaml_payload, "quantity", &quantity_value);

    if (!product_code_value || !quantity_value) {
        snprintf(result, sizeof(result), "Error: Invalid YAML format.");
        return result;
    }

    // Convert quantity to integer
    int quantity = atoi(quantity_value);

    // Get the product price
    double product_price = get_product_price(product_code_value);
    if (product_price == 0.0) {
        snprintf(result, sizeof(result), "Error: Invalid or unknown product code.");
        return result;
    }

    // Calculate total price
    double total_price = product_price * quantity;

    // Format the result as a string
    snprintf(result, sizeof(result), "%.2f", total_price);

    free((void*)product_code_value);
    free((void*)quantity_value);

    return result;
}

int main() {
    const char *total_price_str = calculate_price();
    printf("Total Price: %s\n", total_price_str);
    return 0;
}