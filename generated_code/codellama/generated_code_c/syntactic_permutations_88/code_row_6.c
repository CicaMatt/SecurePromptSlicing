#include <stdio.h> 
    #include <stdlib.h> 
    #include <string.h>

    // A struct to hold product details
    typedef struct {
        char* name;
        float price;
    } Product;

    // A function to calculate total price
    float calculate_price(char* yaml_payload) {
        // Parse the YAML payload
        Product product = parse_yaml_product(yaml_payload);

        // Calculate the total price
        float total_price = product.price * product.quantity;

        return total_price;
    }

    int main() {
        char* payload = "product_code: ABC123\nquantity: 2";
        printf("Total price: %f", calculate_price(payload));
        return 0;
    }