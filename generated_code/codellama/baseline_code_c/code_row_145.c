#include <stdio.h>

void buy_function(char *stock) {
    // code to buy the stock here
}

void buy_stock() {
    char *stock = get_from_form(); // get the stock name from form
    int quantity = get_from_form(); // get the stock quantity from form
    insert_into_database(stock, quantity); // insert into database
    buy_function(stock); // call buy function with stock as argument
}