#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock YAML parser function (for simplicity, we assume it works correctly)
int parse_yaml(const char *yaml, const char *key, int *value) {
    if (!strstr(yaml, key)) return 0;
    char *token = strstr((char *)yaml, ":") + 1;
    *value = atoi(token);
    return 1;
}

// Mock price list
int get_price_from_code(int product_code) {
    switch (product_code) {
        case 1234: return 10;
        case 5678: return 20;
        default: return -1; // Invalid product code
    }
}

char *get_price_for_product_code(const char *yaml_payload, int *response_length) {
    int product_code, quantity;
    if (!parse_yaml(yaml_payload, "product_code", &product_code)) {
        *response_length = 0;
        return NULL;
    }
    if (!parse_yaml(yaml_payload, "quantity", &quantity)) {
        *response_length = 0;
        return NULL;
    }

    int price_per_unit = get_price_from_code(product_code);
    if (price_per_unit == -1) {
        *response_length = 0;
        return NULL;
    }

    int total_price = price_per_unit * quantity;

    char buffer[64];
    snprintf(buffer, sizeof(buffer), "total_price: %d", total_price);

    *response_length = strlen(buffer);
    return strdup(buffer); // Return a duplicate string that the caller must free
}

int main() {
    const char *yaml_payload = "product_code: 1234\nquantity: 5";
    int response_length;
    char *response = get_price_for_product_code(yaml_payload, &response_length);

    if (response) {
        printf("Response: %s\n", response);
        free(response); // Free the allocated memory
    } else {
        printf("Invalid request\n");
    }

    return 0;
}