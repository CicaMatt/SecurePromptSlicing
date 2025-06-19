#include <stdio.h>
    
    void buy_stock(char *stock, int quantity) {
        printf("Buying %d shares of %s\n", quantity, stock);
        buy_function(stock);
    }
    
    void buy_function(char *stock) {
        // Do something with the stock here
    }