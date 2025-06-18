#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    char* calculate_price(char* yaml_payload){
        // Parsing the payload to extract the product code and quantity
        char* product_code = strtok(yaml_payload, " ");
        int quantity = atoi(strtok(NULL, " "));
        
        // Determine the price of the product
        float price = 0;
        if(strcmp(product_code, "PRDCT1") == 0){
            price = 25.99;
        }else if(strcmp(product_code, "PRDCT2") == 0){
            price = 36.78;
        }else{
            // Return an error message as a string
            return "Error: Invalid product code";
        }
        
        // Calculate the total price by multiplying the price of the product by the quantity
        float total_price = price * quantity;
        
        // Convert the total price to a string and return it
        char* result = (char*) malloc(100);
        sprintf(result, "%f", total_price);
        return result;
    }