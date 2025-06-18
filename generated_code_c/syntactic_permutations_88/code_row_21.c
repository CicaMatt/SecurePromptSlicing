#include <stdlib.h>
    #include <stdio.h>

    // Calculates the total price based on product_code and quantity
    char* calculate_price(char* yaml) {
        int quantity = 0;
        float price = 0;
        char* product_code;
        char* total_price;
        // parse YAML payload
        // extract product_code and quantity
        // calculate total price by multiplying price by quantity
        return total_price;
    }

    int main() {
        char* yaml = "product_code: ABC123\nquantity: 2";
        char* result = calculate_price(yaml);
        printf("Total price is: %s", result);
        free(result);
        return 0;
    }