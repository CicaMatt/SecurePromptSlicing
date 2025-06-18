#include <stdio.h>
    #include <stdlib.h>
    #include <string.h> 

    int calculate_price(char* yaml) {
        /* YAML parsing code goes here */
        return 100;
    }

    void main() {
        char *query = "product_code: ABC, quantity: 2";
        int total_price = calculate_price(query);
        printf("Total price is %d", total_price);
    }