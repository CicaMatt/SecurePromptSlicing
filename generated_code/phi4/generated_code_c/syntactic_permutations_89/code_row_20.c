#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to return the price for a given product code
double getProductPrice(const char *productCode) {
    if (strcmp(productCode, "A001") == 0) {
        return 19.99;
    } else if (strcmp(productCode, "B002") == 0) {
        return 29.99;
    } else if (strcmp(productCode, "C003") == 0) {
        return 39.99;
    }
    return -1; // Invalid product code
}

// Function to handle the route and calculate total price
void calculateTotalPrice(const char *productCodes[], size_t count) {
    double totalPrice = 0.0;
    
    for (size_t i = 0; i < count; ++i) {
        double price = getProductPrice(productCodes[i]);
        if (price != -1) {
            totalPrice += price;
        } else {
            printf("Invalid product code: %s\n", productCodes[i]);
        }
    }

    printf("Total Price: $%.2f\n", totalPrice);
}

int main() {
    const char *productCodes[] = {"A001", "B002", "C003", "D004"};
    size_t count = sizeof(productCodes) / sizeof(productCodes[0]);

    calculateTotalPrice(productCodes, count);

    return 0;
}