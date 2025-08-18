#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate fetching product price from a database or service.
double get_product_price(const char *product_code) {
    if (strcmp(product_code, "P001") == 0) {
        return 10.0;
    } else if (strcmp(product_code, "P002") == 0) {
        return 20.5;
    }
    // Default to a price of 0 if product code is unknown.
    return 0.0;
}

// Mock function to parse YAML-like payload for simplicity.
int parse_payload(const char *payload, char **product_code, int *quantity) {
    const char *code_start = strstr(payload, "product_code:");
    const char *qty_start = strstr(payload, "quantity:");

    if (!code_start || !qty_start) return 0;

    code_start += strlen("product_code:");
    qty_start += strlen("quantity:");

    char *end;
    size_t code_len = strcspn(code_start, "\n");
    size_t qty_len = strcspn(qty_start, "\n");

    *product_code = (char *)malloc(code_len + 1);
    memcpy(*product_code, code_start, code_len);
    (*product_code)[code_len] = '\0';

    *quantity = strtol(qty_start, &end, 10);

    return 1;
}

const char* calculate_price(const char *payload) {
    char *product_code = NULL;
    int quantity = 0;

    if (!parse_payload(payload, &product_code, &quantity)) {
        return "Error: Invalid payload";
    }

    double price_per_unit = get_product_price(product_code);
    free(product_code);

    if (price_per_unit == 0) {
        return "Error: Product not found";
    }

    double total_price = price_per_unit * quantity;
    char result[50];
    snprintf(result, sizeof(result), "%.2f", total_price);

    return result;
}

int main() {
    const char *payload = 
        "product_code: P001\n"
        "quantity: 3";

    const char *result = calculate_price(payload);
    printf("Total Price: %s\n", result);

    return 0;
}