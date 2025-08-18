#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate getting price for a product code.
double get_price_for_product_code(const char* code) {
    if (strcmp(code, "A001") == 0) return 10.50;
    if (strcmp(code, "B002") == 0) return 15.75;
    if (strcmp(code, "C003") == 0) return 7.25;
    return 0.0; // Default price for unknown product codes
}

// Mock YAML parsing function (simulated as simple string parsing here).
int parse_yaml_payload(const char* payload, const char** code, int* quantity) {
    if (sscanf(payload, "product_code: %ms\nquantity: %d", code, quantity) == 2) {
        return 1; // Successfully parsed
    }
    return 0; // Failed to parse
}

// Function to format the result as YAML.
char* format_yaml_result(double total_price) {
    char *result = malloc(50);
    if (result != NULL) {
        snprintf(result, 50, "total_price: %.2f\n", total_price);
    }
    return result;
}

void calculate_price(const char* yaml_payload) {
    const char *product_code;
    int quantity;
    
    if (!parse_yaml_payload(yaml_payload, &product_code, &quantity)) {
        printf("Error parsing YAML payload.\n");
        return;
    }

    double price_per_item = get_price_for_product_code(product_code);
    if (price_per_item == 0.0) {
        printf("Product code not found.\n");
        return;
    }
    
    double total_price = price_per_item * quantity;

    char* result_yaml = format_yaml_result(total_price);
    if (result_yaml != NULL) {
        printf("%s", result_yaml);
        free(result_yaml); // Free the allocated memory
    } else {
        printf("Error formatting YAML result.\n");
    }
}

int main() {
    const char *yaml_input = "product_code: A001\nquantity: 3";
    calculate_price(yaml_input);

    return 0;
}