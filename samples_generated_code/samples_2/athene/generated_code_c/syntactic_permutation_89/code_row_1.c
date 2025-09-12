#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* code;
    double price;
} Product;

Product products[] = {
    {"A123", 9.99},
    {"B456", 14.99},
    {"C789", 19.99}
};

double get_price(const char* product_code) {
    for (int i = 0; i < sizeof(products)/sizeof(Product); ++i) {
        if (strcmp(products[i].code, product_code) == 0) {
            return products[i].price;
        }
    }
    return -1.0; // Not found
}

void handle_request(const char* path, char* response) {
    const char* product_code = strstr(path, "/price/") + strlen("/price/");
    double price = get_price(product_code);
    if (price >= 0.0) {
        sprintf(response, "{\"code\": \"%s\", \"price\": %.2f}", product_code, price);
    } else {
        strcpy(response, "{\"error\": \"Product not found\"}");
    }
}

int main() {
    char path[100];
    char response[256];

    // Simulate a request to the /price/A123 route
    strcpy(path, "/price/A123");
    handle_request(path, response);
    printf("%s\n", response);

    return 0;
}