#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

void parse_yaml_payload(const char *payload, KeyValuePair *product_code, KeyValuePair *quantity) {
    const char *start = payload;
    while ((start = strstr(start, "product_code:")) != NULL) {
        start += strlen("product_code:");
        char *end = strchr(start, '\n');
        if (end) {
            *end = '\0';
            product_code->key = strdup("product_code");
            product_code->value = strdup(start);
            return;
        }
    }

    while ((start = strstr(start, "quantity:")) != NULL) {
        start += strlen("quantity:");
        char *end = strchr(start, '\n');
        if (end) {
            *end = '\0';
            quantity->key = strdup("quantity");
            quantity->value = strdup(start);
            return;
        }
    }
}

double get_product_price(const char *product_code) {
    // Simple hardcoded product prices for demonstration
    if (strcmp(product_code, "A001") == 0) return 10.0;
    if (strcmp(product_code, "B002") == 0) return 20.5;
    if (strcmp(product_code, "C003") == 0) return 30.75;

    // Default to $0 for unknown products
    return 0.0;
}

const char* calculate_price(const char *payload) {
    KeyValuePair product_code = {NULL, NULL};
    KeyValuePair quantity = {NULL, NULL};

    parse_yaml_payload(payload, &product_code, &quantity);

    if (product_code.value == NULL || quantity.value == NULL) {
        return "Invalid payload";
    }

    double price = get_product_price(product_code.value);
    int qty = atoi(quantity.value);
    double total_price = price * qty;

    char *result = malloc(BUFFER_SIZE);
    snprintf(result, BUFFER_SIZE, "%.2f", total_price);

    free(product_code.key);
    free(product_code.value);
    free(quantity.key);
    free(quantity.value);

    return result;
}

int main() {
    const char *yaml_payload = "product_code: A001\nquantity: 3";
    
    const char *total_price_str = calculate_price(yaml_payload);
    printf("Total Price: %s\n", total_price_str);

    free((void*)total_price_str); // Free the returned string
    return 0;
}