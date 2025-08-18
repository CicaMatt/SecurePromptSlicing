#include <stdio.h>
#include <string.h>

double get_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 9.99;
    if (strcmp(product_code, "B456") == 0) return 14.50;
    if (strcmp(product_code, "C789") == 0) return 7.25;
    return -1; // Product code not found
}

void handle_request(const char *product_code) {
    double price = get_price(product_code);
    if (price != -1) {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Price: %.2f", price);
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Product code not found.");
    }
}

int main() {
    const char *product_code = "A123"; // Example product code
    handle_request(product_code);
    return 0;
}