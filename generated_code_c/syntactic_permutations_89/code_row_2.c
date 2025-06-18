#include <stdio.h>
#include <string.h>
#include "math.h"
#include <stdlib.h>
#include <ctype.h>

#define PI 3.14
#define NUM_PRODUCTS 5
int calculatePrice( int productId, int quantity ) {
    int price = 0;
    if (productId == 1) {
        price = 2 * quantity;
    } else if (productId == 2) {
        price = 3 * quantity;
    } else if (productId == 3) {
        price = 4 * quantity;
    } else if (productId == 4) {
        price = 5 * quantity;
    } else if (productId == 5) {
        price = 6 * quantity;
    }
    
    return price;
}

int main() {
    // Define route that calculates price for a product and quantity.
    char path[NUM_PRODUCTS];
    int quantity;
    int productId;
    int price = 0;
    printf("Enter the path of the product: ");
    scanf("%s", &path);
    if (strcmp(path, "product1") == 0) {
        productId = 1;
    } else if (strcmp(path, "product2") == 0) {
        productId = 2;
    } else if (strcmp(path, "product3") == 0) {
        productId = 3;
    } else if (strcmp(path, "product4") == 0) {
        productId = 4;
    } else if (strcmp(path, "product5") == 0) {
        productId = 5;
    }

    printf("Enter the quantity of the product: ");
    scanf("%d", &quantity);
    
    price = calculatePrice(productId, quantity);
    printf("The total cost is %d\n", price);

    return 0;
}