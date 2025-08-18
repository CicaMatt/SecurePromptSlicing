#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 100

typedef struct {
    char code[10];
    float price;
} Product;

Product products[MAX_PRODUCTS] = {
    {"P001", 19.99},
    {"P002", 29.99},
    {"P003", 39.99}
};

int product_count = 3;

float get_price(const char *code) {
    for (int i = 0; i < product_count; ++i) {
        if (strcmp(products[i].code, code) == 0) {
            return products[i].price;
        }
    }
    return -1.0f; // Return -1.0 to indicate not found
}

void route_get_price(const char *path) {
    char product_code[10] = {0};
    
    if (strncmp(path, "/get_price/", 11) == 0 && strlen(path) <= 21) {
        strncpy(product_code, path + 11, sizeof(product_code) - 1);
        
        float price = get_price(product_code);
        if (price != -1.0f) {
            printf("200 OK\nPrice: $%.2f\n", price);
        } else {
            printf("404 Not Found\nProduct code not found.\n");
        }
    } else {
        printf("400 Bad Request\nInvalid route or product code length.\n");
    }
}

int main() {
    char input[50];
    
    printf("Enter the route: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; // Remove newline character
    
    route_get_price(input);
    
    return 0;
}