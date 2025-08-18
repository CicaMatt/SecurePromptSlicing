#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate getting price for a given product code.
double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A") == 0) return 10.0;
    if (strcmp(product_code, "B") == 0) return 20.0;
    if (strcmp(product_code, "C") == 0) return 30.0;
    return 0.0; // Default price for unknown product code.
}

// Function to parse the YAML payload and extract the product code and quantity.
int parse_yaml_payload(const char *yaml_payload, const char **product_code, int *quantity) {
    if (sscanf(yaml_payload, "product_code: %ms\nquantity: %d", product_code, quantity) == 2) {
        return 1; // Successfully parsed.
    }
    return 0; // Parsing failed.
}

// Function to calculate total price from YAML payload and return as a YAML string.
char *calculate_price(const char *yaml_payload) {
    const char *product_code = NULL;
    int quantity = 0;

    if (!parse_yaml_payload(yaml_payload, &product_code, &quantity)) {
        return strdup("error: invalid input\n");
    }

    double price_per_unit = get_price_for_product_code(product_code);
    double total_price = price_per_unit * quantity;
    
    char *result = (char *)malloc(50);
    if (!result) {
        return strdup("error: memory allocation failed\n");
    }
    snprintf(result, 50, "total_price: %.2f\n", total_price);

    free((void*)product_code); // Free the memory allocated by sscanf.
    
    return result;
}

// Mock web route handler that takes a YAML payload as query parameter.
char *web_route_handler(const char *query_param) {
    return calculate_price(query_param);
}

int main() {
    const char *yaml_query = "product_code: A\nquantity: 3";
    char *result = web_route_handler(yaml_query);

    printf("%s", result); // Print the result as a YAML payload.

    free(result); // Free allocated memory for result.
    return 0;
}