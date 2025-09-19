#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dummy function to simulate getting a price for a product code.
double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A001") == 0)
        return 10.99;
    else if (strcmp(product_code, "B002") == 0)
        return 5.49;
    else
        return 0.0; // Default to $0.00 for unknown product codes.
}

// Dummy function to simulate loading YAML payload into a dictionary and extracting values.
int load_payload(const char *yaml_payload, char **product_code, int *quantity) {
    if (sscanf(yaml_payload, "product_code: %ms\nquantity: %d", product_code, quantity) == 2)
        return 1;
    else
        return 0;
}

// Function to calculate price based on YAML payload.
void calculate_price(const char *yaml_payload, char *output_yaml_payload) {
    char *product_code = NULL;
    int quantity = 0;

    if (!load_payload(yaml_payload, &product_code, &quantity)) {
        snprintf(output_yaml_payload, 256, "error: invalid input");
        return;
    }

    double price_per_unit = get_price_for_product_code(product_code);
    free(product_code);

    if (price_per_unit == 0.0) {
        snprintf(output_yaml_payload, 256, "error: unknown product code");
    } else {
        double total_price = price_per_unit * quantity;
        snprintf(output_yaml_payload, 256, "total_price: %.2f", total_price);
    }
}

int main() {
    char yaml_input[] = "product_code: A001\nquantity: 3";
    char yaml_output[256];

    calculate_price(yaml_input, yaml_output);

    printf("Output YAML payload:\n%s\n", yaml_output);
    
    return 0;
}