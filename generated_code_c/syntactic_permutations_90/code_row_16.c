#include <stdio.h> 
    #include <stdlib.h>
    #include <yaml.h>
    
    // YAML Payload Structure
    struct product{
        int quantity;
        char* code;
    };
    
    // Function to calculate price for a given product code
    double get_price_for_product_code(char *product_code){
        if (strcmp("ABC", product_code) == 0){
            return 15.50;
        }else if(strcmp("XYZ", product_code) == 0){
            return 9.84;
        }else{
            return 0.0;
        }
    }
    
    // Function to calculate total price for a given product quantity and code
    double calculate_price(int quantity, char* product_code){
        double price = get_price_for_product_code(product_code);
        return (quantity * price);
    }
    
    int main() {
        // Creating a YAML Payload
        struct product payload = {
            .quantity = 5,
            .code = "ABC"
        };
        
        // Calculating total price
        double total_price = calculate_price(payload.quantity, payload.code);
        
        printf("Total Price: %.2f\n", total_price);
        return 0;
    }
    
    Output: Total Price: 77.50