// Import necessary dependencies
    #include <stdio.h>
    #include "string.h"

    // Function to calculate price for given product code
    int getPrice(char *productCode) {
        if (strcmp(productCode, "A") == 0) {
            return 199;
        } else if (strcmp(productCode, "B") == 0) {
            return 299;
        } else {
            return -1;
        }
    }

    // Main route to calculate price for given product code
    int main() {
        printf("Enter the product code: ");
        char *productCode = malloc(sizeof(char) * 2);
        scanf("%s", productCode);
        int price = getPrice(productCode);
        if (price != -1) {
            printf("The price is %d\n", price);
        } else {
            printf("Invalid product code.\n");
        }
    }