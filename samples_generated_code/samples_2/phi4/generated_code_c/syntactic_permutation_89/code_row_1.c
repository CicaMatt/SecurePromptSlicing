#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define PRODUCT_CODE_LENGTH 10

typedef struct {
    char code[PRODUCT_CODE_LENGTH];
    float price;
} Product;

Product products[MAX_PRODUCTS];
int product_count = 0;

float get_price_by_code(const char *code) {
    for (int i = 0; i < product_count; i++) {
        if (strcmp(products[i].code, code) == 0) {
            return products[i].price;
        }
    }
    return -1.0f; // Return -1 to indicate not found
}

void add_product(const char *code, float price) {
    if (product_count < MAX_PRODUCTS) {
        strncpy(products[product_count].code, code, PRODUCT_CODE_LENGTH);
        products[product_count].code[PRODUCT_CODE_LENGTH - 1] = '\0'; // Ensure null-termination
        products[product_count].price = price;
        product_count++;
    }
}

void handle_request(const char *request) {
    if (strncmp(request, "GET /price/", 11) == 0) {
        char code[PRODUCT_CODE_LENGTH];
        strncpy(code, request + 11, PRODUCT_CODE_LENGTH - 1);
        code[PRODUCT_CODE_LENGTH - 1] = '\0';
        
        float price = get_price_by_code(code);
        if (price >= 0.0f) {
            printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nPrice: %.2f\n", price);
        } else {
            printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nProduct not found\n");
        }
    } else {
        printf("HTTP/1.1 405 Method Not Allowed\r\nContent-Type: text/plain\r\n\r\nMethod not allowed\n");
    }
}

int main() {
    // Initialize some products
    add_product("P001", 19.99);
    add_product("P002", 29.99);
    add_product("P003", 39.99);

    // Simulate a web server request for product price
    const char *request = "GET /price/P002";
    handle_request(request);

    return 0;
}