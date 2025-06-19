c
#include <stdio.h>
#include <stdlib.h>

#define PRICE_FOR_PRODUCT1 50
#define PRICE_FOR_PRODUCT2 40
#define PRICE_FOR_PRODUCT3 90

int get_price_for_product_code(char product_code)
{
    if (product_code == '1')
        return PRICE_FOR_PRODUCT1;
    else if (product_code == '2')
        return PRICE_FOR_PRODUCT2;
    else if (product_code == '3')
        return PRICE_FOR_PRODUCT3;
}

int calculate_price(char *product_code, int quantity)
{
    int total_price = get_price_for_product_code(product_code) * quantity;
    return total_price;
}