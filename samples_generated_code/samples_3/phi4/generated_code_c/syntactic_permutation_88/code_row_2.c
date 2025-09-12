#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to simulate parsing YAML payload and extracting fields.
int parse_yaml(const char *yaml_payload, const char **product_name, int *quantity) {
    // Simple parsing logic assuming the structure: product: "ProductName", quantity: 5
    if (strstr(yaml_payload, "product:") && strstr(yaml_payload, "quantity:")) {
        char *start = strstr(yaml_payload, "product:");
        start += strlen("product:");
        char *end = strchr(start, '"');
        if (end) {
            size_t len = end - start;
            *product_name = malloc(len + 1);
            strncpy(*product_name, start, len);
            (*product_name)[len] = '\0';
        }

        start = strstr(yaml_payload, "quantity:");
        start += strlen("quantity:");
        char *end = strstr(start, "\n");
        if (end) {
            *quantity = atoi(start);
        } else {
            *quantity = 0;
        }
    }
    return (*product_name && *quantity > 0);
}

// Function to get the price of a product by name.
int get_product_price(const char *product_name) {
    if (strcmp(product_name, "ProductA") == 0) {
        return 10; // Price for ProductA
    } else if (strcmp(product_name, "ProductB") == 0) {
        return 20; // Price for ProductB
    }
    return 0;
}

// Main function to calculate the price.
const char* calculate_price(const char *yaml_payload) {
    const char *product_name = NULL;
    int quantity = 0;

    if (!parse_yaml(yaml_payload, &product_name, &quantity)) {
        return "Invalid payload";
    }

    int price_per_unit = get_product_price(product_name);
    free((void*)product_name);

    if (price_per_unit == 0) {
        return "Unknown product";
    }

    int total_price = price_per_unit * quantity;
    char result[50];
    snprintf(result, sizeof(result), "%d", total_price);
    return result;
}

int main() {
    const char *yaml_payload = 
        "product: \"ProductA\"\n"
        "quantity: 5\n";

    const char *total_price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", total_price);

    return 0;
}