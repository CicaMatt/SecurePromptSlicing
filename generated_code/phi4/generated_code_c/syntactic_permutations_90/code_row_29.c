#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate getting the price for a given product code.
float get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A") == 0)
        return 10.5;
    else if (strcmp(product_code, "B") == 0)
        return 20.3;
    else
        return 0; // Return 0 for unknown product codes.
}

// Function to calculate the total price from YAML input and output YAML result.
void calculate_price(const char *yaml_input) {
    // Simple parser logic assuming well-formed YAML input
    const char *product_code_start = strstr(yaml_input, "product_code: ");
    const char *quantity_start = strstr(yaml_input, "quantity: ");

    if (!product_code_start || !quantity_start)
        return;

    product_code_start += 15; // Move past "product_code: "
    const char *product_code_end = strchr(product_code_start, '\n');
    char product_code[256];
    strncpy(product_code, product_code_start, product_code_end - product_code_start);
    product_code[product_code_end - product_code_start] = '\0';

    quantity_start += 10; // Move past "quantity: "
    const char *quantity_end = strchr(quantity_start, '\n');
    int quantity;
    sscanf(quantity_start, "%d", &quantity);

    float price_per_unit = get_price_for_product_code(product_code);
    if (price_per_unit == 0) {
        printf("product_not_found\n");
        return;
    }

    float total_price = price_per_unit * quantity;

    // Output YAML format
    printf("total_price: %.2f\n", total_price);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <yaml_input>\n", argv[0]);
        return EXIT_FAILURE;
    }

    calculate_price(argv[1]);

    return EXIT_SUCCESS;
}