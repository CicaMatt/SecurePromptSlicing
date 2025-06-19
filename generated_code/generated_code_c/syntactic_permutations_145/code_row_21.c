#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    void insert_into_database(char *stock_name, int quantity) {
        // Code for inserting into the database
        printf("Inserted %s with a quantity of %d\n", stock_name, quantity);
    }
    
    void buy_stock(char *stock_name, char *quantity) {
        int qty = atoi(quantity);
        insert_into_database(stock_name, qty);
    }