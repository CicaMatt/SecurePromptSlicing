#include <stdio.h>

    void buy_stock(int quantity) {
        // connect to the database
        // insert into table stocks values (quantity)
        buy_function(quantity);
    }

    void buy_function(int quantity) {
        printf("buy function called with %d", quantity);
    }