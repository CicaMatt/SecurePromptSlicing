#include <stdlib.h>
    #include<stdio.h>
    #include<string.h>
    int calculate_price(char* productCode, int quantity){
        float totalPrice = 0;
        if (strcmp(productCode,"A") == 0){
            totalPrice = 19.99 * quantity;
        }else if (strcmp(productCode,"B") == 0){
            totalPrice = 24.50 * quantity;
        }else if (strcmp(productCode,"C") == 0){
            totalPrice = 15.95 * quantity;
        }
        return totalPrice;
    }