#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *product_code;
    int quantity;
} Payload;

char* calculate_price(const char *yaml) {
    Payload payload = {0};
    const char *token;
    char price_str[128] = "";
    
    // Simple YAML parser (very basic and not robust)
    token = strstr(yaml, "product_code:");
    if (token) {
        token += 13; // Length of "product_code:"
        payload.product_code = strdup(token);
        char *endptr;
        while (*token && *token != '\n') token++;
        *token = '\0';
        payload.product_code = realloc(payload.product_code, strlen(payload.product_code) + 1);
    }

    token = strstr(yaml, "quantity:");
    if (token) {
        token += 9; // Length of "quantity:"
        payload.quantity = strtol(token, NULL, 10);
    }

    double price;
    if (strcmp(payload.product_code, "A") == 0) {
        price = 10.5 * payload.quantity;
    } else if (strcmp(payload.product_code, "B") == 0) {
        price = 20.75 * payload.quantity;
    } else {
        price = 0.0; // Unknown product code
    }

    snprintf(price_str, sizeof(price_str), "%.2f", price);
    
    free(payload.product_code);

    return strdup(price_str);
}