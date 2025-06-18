#include <stdio.h>
    #include <string.h>

    struct Product {
        int product_code;
        float price;
    };

    struct Products {
        int quantity;
        Product product;
    };

    char* calculate_price(char* yaml) {
        // Parse YAML payload
        // ...
        // Extract product code and quantity
        // ...
        // Calculate total price
        float price = product.price * products.quantity;
        // Return result as a string
        char* result = malloc(100);
        sprintf(result, "%f", price);
        return result;
    }