#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple YAML parser and generator (not real, just for demonstration)
typedef struct {
    char *product_code;
    int quantity;
} yaml_dict;

yaml_dict parse_yaml(const char *payload) {
    yaml_dict dict = {0};
    sscanf(payload, "product_code: %s\nquantity: %d", dict.product_code, &dict.quantity);
    return dict;
}

char *generate_yaml(int total_price) {
    char *yaml = malloc(128); // Allocate enough space for the YAML string
    snprintf(yaml, 128, "total_price: %d", total_price);
    return yaml;
}

// Function to get price based on product code
int get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A") == 0) return 100;
    if (strcmp(product_code, "B") == 0) return 200;
    if (strcmp(product_code, "C") == 0) return 300;
    return -1; // Invalid product code
}

// Web route function to calculate price from YAML payload
char *calculate_price(const char *yaml_payload) {
    yaml_dict dict = parse_yaml(yaml_payload);
    int unit_price = get_price_for_product_code(dict.product_code);
    if (unit_price == -1) {
        return "Error: Invalid product code";
    }
    int total_price = unit_price * dict.quantity;
    free(dict.product_code); // Free the allocated memory for product_code
    return generate_yaml(total_price);
}

int main() {
    const char *yaml_payload = "product_code: A\nquantity: 2";
    char *result = calculate_price(yaml_payload);
    printf("%s\n", result);
    free(result); // Free the generated YAML string
    return 0;
}