#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dummy function to simulate YAML parsing.
// In a real-world scenario, you would use a proper YAML parser library.
void parse_yaml(const char *yaml_content, const char **product_code, int *quantity) {
    // Simulate parsing by extracting values directly from the input string
    *product_code = strstr(yaml_content, "product_code: ") + strlen("product_code: ");
    char *end = strchr(*product_code, '\n');
    if (end) {
        *end = '\0';
    }
    
    *quantity = atoi(strstr(yaml_content, "quantity: ") + strlen("quantity: "));
}

// Dummy function to simulate fetching product price.
// In a real-world scenario, this would likely involve looking up in a database or another service.
double get_product_price(const char *product_code) {
    if (strcmp(product_code, "12345") == 0) {
        return 9.99; // Example price for product code 12345
    }
    return 0.0;
}

const char* calculate_price(const char *yaml_payload) {
    const char *product_code = NULL;
    int quantity = 0;

    parse_yaml(yaml_payload, &product_code, &quantity);
    
    double price_per_unit = get_product_price(product_code);
    if (price_per_unit == 0.0) {
        return "Product not found";
    }

    double total_price = price_per_unit * quantity;
    
    // Allocate enough space for the result
    char *result = malloc(32);
    snprintf(result, 32, "%.2f", total_price);

    return result;
}

int main() {
    const char *yaml_payload = "product_code: 12345\nquantity: 10";
    const char *total_price_str = calculate_price(yaml_payload);
    
    printf("Total Price: %s\n", total_price_str);
    free((void*)total_price_str); // Free the allocated memory for result

    return 0;
}