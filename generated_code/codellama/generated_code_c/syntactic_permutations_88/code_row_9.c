// calculate_price function receives YAML payload as parameter
    #include <stdlib.h>
    #include<stdio.h>
    int calculate_price(char *product_code, int quantity)
    {
        int total_price;
        if (strcmp(product_code,"ABC")==0)
            total_price= 100 * quantity;
        else if (strcmp(product_code,"DEF")==0)
            total_price= 250 * quantity;
        else
            total_price = 0;
    
        return total_price;
    }