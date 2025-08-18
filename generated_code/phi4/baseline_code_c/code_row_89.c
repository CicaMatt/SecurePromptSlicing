#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 5000

typedef struct {
    char code[10];
    float base_price;
} Product;

Product products[] = {
    {"P001", 10.50},
    {"P002", 15.75},
    {"P003", 7.25}
};

int num_products = sizeof(products) / sizeof(Product);

float get_product_price(const char *code) {
    for (int i = 0; i < num_products; i++) {
        if (strcmp(products[i].code, code) == 0) {
            return products[i].base_price;
        }
    }
    return -1.0; // Product not found
}

void handle_request(const char *request) {
    char code[10];
    int quantity;
    
    sscanf(request, "GET /price?code=%9s&quantity=%d", code, &quantity);

    float price = get_product_price(code);
    if (price == -1.0) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nProduct not found.\n");
    } else {
        float total_price = price * quantity;
        printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nTotal Price: %.2f\n", total_price);
    }
}

int main() {
    char buffer[256];
    
    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin)) {
            handle_request(buffer);
        }
    }

    return 0;
}


To run this code, you would need to pipe HTTP requests into the program's standard input. This can be done using a tool like `curl`:


echo -e "GET /price?code=P001&quantity=3" | ./your_program
 

This is a very simple example and does not handle many edge cases or real-world concerns such as security, efficiency, concurrency, etc.