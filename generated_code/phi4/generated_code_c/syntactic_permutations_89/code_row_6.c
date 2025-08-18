#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a function to get the price of a product by its code
float getProductPrice(const char *code) {
    if (strcmp(code, "A") == 0) return 10.5;
    if (strcmp(code, "B") == 0) return 20.75;
    if (strcmp(code, "C") == 0) return 15.25;
    return 0; // If product code is not found
}

// Define a function to calculate total price based on the product code and quantity
float calculateTotalPrice(const char *code, int quantity) {
    float unitPrice = getProductPrice(code);
    if (unitPrice == 0) {
        printf("Product code not found.\n");
        return -1;
    }
    return unitPrice * quantity;
}

// Simple HTTP server simulation to handle requests
void handleRequest(const char *request) {
    // Simulate extracting product code and quantity from the request
    const char *code = "A";  // Example: Extracted from request
    int quantity = 3;        // Example: Extracted from request

    float totalPrice = calculateTotalPrice(code, quantity);
    if (totalPrice >= 0) {
        printf("Total price for product code %s and quantity %d is %.2f\n", code, quantity, totalPrice);
    }
}

int main() {
    const char *request = "GET /calculate_price"; // Example request
    handleRequest(request);

    return 0;
}