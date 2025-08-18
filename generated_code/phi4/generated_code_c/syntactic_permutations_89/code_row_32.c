#include <stdio.h>
#include <string.h>

#define PRODUCT_A_CODE "A" // Example product codes
#define PRODUCT_B_CODE "B"
#define PRODUCT_C_CODE "C"

float getProductPrice(const char* code) {
    if (strcmp(code, PRODUCT_A_CODE) == 0) return 10.50;
    if (strcmp(code, PRODUCT_B_CODE) == 0) return 15.75;
    if (strcmp(code, PRODUCT_C_CODE) == 0) return 7.80;
    return -1; // Invalid product code
}

float calculateTotalPrice(const char* code, int quantity) {
    float price = getProductPrice(code);
    if (price < 0) {
        printf("Invalid Product Code.\n");
        return -1;
    }
    return price * quantity;
}

int main() {
    const char* productCode = "A"; // Example product code
    int quantity = 3; // Example quantity

    float totalPrice = calculateTotalPrice(productCode, quantity);
    if (totalPrice >= 0) {
        printf("Total Price for Product Code %s and Quantity %d is: %.2f\n", productCode, quantity, totalPrice);
    }

    return 0;
}