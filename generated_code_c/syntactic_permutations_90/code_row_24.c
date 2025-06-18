#include <stdio.h>
#include <stdlib.h>

#define PRODUCT_1  "VOUCHER"
#define PRICE_1    50
#define PRODUCT_2  "TSHIRT"
#define PRICE_2    20
#define PRODUCT_3  "MUG"
#define PRICE_3    75

int get_price_for_product_code(char *product_code){
    if (strcmp(PRODUCT_1, product_code) == 0) return PRICE_1;
    else if (strcmp(PRODUCT_2, product_code) == 0) return PRICE_2;
    else if (strcmp(PRODUCT_3, product_code) == 0) return PRICE_3;
}

char *calculate_price(char *query_param){
    // load yaml payload into dictionary
    // extract product_code and quantity
    // calculate total price
    // return total_price as yaml payload
}