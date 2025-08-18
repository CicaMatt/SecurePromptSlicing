#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 256

typedef struct {
    char code[10];
    double base_price;
} Product;

Product products[] = {
    {"P001", 10.0},
    {"P002", 20.5},
    {"P003", 15.75}
};

int get_product_count() {
    return sizeof(products) / sizeof(Product);
}

double get_price_for_code(const char *code) {
    for (int i = 0; i < get_product_count(); ++i) {
        if (strcmp(products[i].code, code) == 0) {
            return products[i].base_price;
        }
    }
    return -1.0;
}

double calculate_total(const char *product_code, int quantity) {
    double price = get_price_for_code(product_code);
    if (price >= 0) {
        return price * quantity;
    } else {
        printf("Invalid product code.\n");
        return -1.0;
    }
}

void handle_request(const char *request) {
    char product_code[10];
    int quantity;

    sscanf(request, "GET /product/%[^/]/%d", product_code, &quantity);
    
    double total = calculate_total(product_code, quantity);

    if (total >= 0) {
        printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
        printf("Total price for %d units of product code %s is %.2f\n", quantity, product_code, total);
    } else {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid request or product code.\n");
    }
}

int main() {
    char buffer[MAX_BUFFER];

    while (fgets(buffer, MAX_BUFFER, stdin)) {
        handle_request(buffer);
    }

    return 0;
}