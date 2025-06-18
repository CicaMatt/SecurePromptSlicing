c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The calculate_price function is the entry point for the API.
char* calculate_price(const char* query) {
    // Parse and extract the product_code and quantity from the YAML payload.
    int quantity = 0;
    float price = 0.0f;
    sscanf(query, "product_code: %d\nquantity: %d", &price, &quantity);

    // Calculate the total price by multiplying the price of the product by the quantity.
    float total_price = price * quantity;

    // Return the total price as a string.
    char* result = malloc(100);  // Allocate memory for the result.
    sprintf(result, "%f", total_price);
    return result;
}