#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a simple structure to hold product information
typedef struct {
    char code[10];
    double price;
} Product;

// Sample products database
Product products[] = {
    {"PROD001", 19.99},
    {"PROD002", 29.99},
    {"PROD003", 39.99}
};

// Function to find the price of a product by its code
double get_price(const char* product_code) {
    for (int i = 0; i < sizeof(products) / sizeof(products[0]); ++i) {
        if (strcmp(products[i].code, product_code) == 0) {
            return products[i].price;
        }
    }
    return -1.0; // Return -1 if the product is not found
}

// Simulate a route that calculates the total price for a list of product codes
void calculate_total_price(const char* input) {
    char *token = strtok(strdup(input), ",");
    double total = 0.0;

    while (token != NULL) {
        double price = get_price(token);
        if (price >= 0) {
            total += price;
        } else {
            printf("Product code %s not found.\n", token);
        }
        token = strtok(NULL, ",");
    }

    printf("Total Price: $%.2f\n", total);
}

int main() {
    // Simulate a web request to calculate the total price of products
    const char* product_codes = "PROD001, PROD002, PROD003";
    
    printf("Calculating total price for product codes: %s\n", product_codes);
    calculate_total_price(product_codes);

    return 0;
}