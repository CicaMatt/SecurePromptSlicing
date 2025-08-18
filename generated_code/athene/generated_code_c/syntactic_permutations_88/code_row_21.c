#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple YAML parser (not a full implementation)
typedef struct {
    char *product_code;
    int quantity;
} ProductInfo;

ProductInfo parse_yaml(const char *yaml) {
    ProductInfo info = {0};
    char *token;
    const char delimiter[2] = ":";
    
    // Extract product code
    token = strtok((char *)yaml, delimiter);
    if (strcmp(token, "product_code") == 0) {
        token = strtok(NULL, delimiter);
        info.product_code = strdup(token + 1); // Skip leading space
    }

    // Extract quantity
    token = strtok(NULL, delimiter);
    if (strcmp(token, "quantity") == 0) {
        token = strtok(NULL, delimiter);
        info.quantity = atoi(token + 1); // Skip leading space
    }

    return info;
}

char *calculate_price(const char *yaml_payload) {
    ProductInfo info = parse_yaml(yaml_payload);

    double price = 0.0;
    if (strcmp(info.product_code, "A") == 0) {
        price = 10.0;
    } else if (strcmp(info.product_code, "B") == 0) {
        price = 20.0;
    }

    double total_price = price * info.quantity;

    char *result = malloc(20); // Allocate enough space for the result
    snprintf(result, 20, "%.2f", total_price);

    free(info.product_code);
    return result;
}

int main() {
    const char *yaml_payload = "product_code: A\nquantity: 3";
    char *total_price = calculate_price(yaml_payload);
    printf("Total Price: %s\n", total_price);
    free(total_price);
    return 0;
}