#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to get price for a given product code
float get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "P001") == 0) return 10.0;
    if (strcmp(product_code, "P002") == 0) return 20.5;
    if (strcmp(product_code, "P003") == 0) return 15.75;
    return -1; // Invalid product code
}

// Simple YAML parser for this example
typedef struct {
    char product_code[10];
    int quantity;
} Payload;

Payload parse_yaml_payload(const char *yaml) {
    Payload payload = { .product_code[0] = '\0', .quantity = 0 };
    
    const char *key, *value, *ptr = yaml;
    while ((ptr = strstr(ptr, "product_code:")) != NULL) {
        ptr += strlen("product_code:");
        key = strtok((char *)ptr, "\n");
        value = strtok(NULL, "\n");
        if (value && strlen(value) > 0) {
            strncpy(payload.product_code, value + 1, sizeof(payload.product_code) - 1);
        }
    }

    while ((ptr = strstr(ptr, "quantity:")) != NULL) {
        ptr += strlen("quantity:");
        key = strtok((char *)ptr, "\n");
        value = strtok(NULL, "\n");
        if (value && strlen(value) > 0) {
            payload.quantity = atoi(value);
        }
    }

    return payload;
}

// Function to calculate price from YAML payload
const char* calculate_price(const char *yaml_payload) {
    Payload payload = parse_yaml_payload(yaml_payload);

    float unit_price = get_price_for_product_code(payload.product_code);
    if (unit_price == -1) {
        return "{ error: 'Invalid product code' }";
    }

    float total_price = unit_price * payload.quantity;
    
    char response[256];
    snprintf(response, sizeof(response), "{ total_price: %.2f }\n", total_price);

    return response;
}

int main() {
    const char *yaml_payload = 
        "product_code: P001\n"
        "quantity: 3";

    const char *result = calculate_price(yaml_payload);
    printf("%s\n", result);

    return 0;
}