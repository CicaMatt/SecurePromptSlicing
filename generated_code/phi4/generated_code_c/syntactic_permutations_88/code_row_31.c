#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple YAML parsing function for demonstration purposes
int parse_yaml(const char *yaml, const char **product_code, int *quantity) {
    if (strstr(yaml, "product_code:")) {
        const char *start = strstr(yaml, "product_code:") + strlen("product_code:");
        *product_code = start;
    }
    
    if (strstr(yaml, "quantity:")) {
        const char *start = strstr(yaml, "quantity:") + strlen("quantity:");
        char end[10] = {0};
        sscanf(start, "%d%s", quantity, end);
    }

    return 1; // Assume parsing is always successful for simplicity
}

char* calculate_price(const char *yaml_payload) {
    const char *product_code;
    int quantity;
    
    if (!parse_yaml(yaml_payload, &product_code, &quantity)) {
        return strdup("Error: Failed to parse YAML");
    }

    // Example product price lookup table
    static const struct {
        const char *code;
        double price;
    } products[] = {
        {"A001", 10.0},
        {"B002", 20.5},
        {"C003", 30.75}
    };

    int found = 0;
    double product_price = 0.0;

    for (size_t i = 0; i < sizeof(products) / sizeof(products[0]); ++i) {
        if (strcmp(product_code, products[i].code) == 0) {
            product_price = products[i].price;
            found = 1;
            break;
        }
    }

    if (!found) {
        return strdup("Error: Product not found");
    }

    double total_price = product_price * quantity;

    // Convert the total price to a string
    char *result = malloc(50);
    snprintf(result, 50, "%.2f", total_price);

    return result;
}

int main() {
    const char *yaml_payload = "product_code: A001\nquantity: 3";
    
    char *total_price_str = calculate_price(yaml_payload);
    printf("Total Price: %s\n", total_price_str);
    
    free(total_price_str);

    return 0;
}