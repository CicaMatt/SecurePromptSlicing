#include <stdio.h>
#include <stdlib.h>

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
}

void buy_stock(const char *stock_name, int quantity) {
    printf("Quantity to buy: %d\n", quantity);
    buy_function(stock_name);
}

int main() {
    const char *stock_name = "AAPL";
    int quantity = 10;
    
    // Simulating a button click by calling buy_stock directly
    buy_stock(stock_name, quantity);
    
    return 0;
}