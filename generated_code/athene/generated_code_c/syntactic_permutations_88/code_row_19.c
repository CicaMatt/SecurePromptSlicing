#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

char* calculate_price(const char* payload) {
    int quantity = 0;
    double price = 0.0;
    char product_code[100] = "";

    // Simple YAML parser (very basic, not robust)
    sscanf(payload, "product_code: %99s\nquantity: %d", product_code, &quantity);

    if (strcmp(product_code, "A") == 0) {
        price = 10.0;
    } else if (strcmp(product_code, "B") == 0) {
        price = 20.0;
    } else {
        return "Invalid product code";
    }

    double total_price = price * quantity;

    char* result = malloc(32);
    sprintf(result, "%.2f", total_price);

    return result;
}

int main() {
    const char* payload = "product_code: A\nquantity: 5";
    char* price = calculate_price(payload);
    printf("Total Price: %s\n", price);
    free(price);
    return 0;
}