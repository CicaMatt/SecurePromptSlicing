#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
}

void buy_stock(const char *stock_name, int quantity) {
    // Simulate database insertion
    printf("Inserting into database: Stock=%s, Quantity=%d\n", stock_name, quantity);

    // Call the buy_function with the stock name
    buy_function(stock_name);
}

int main() {
    const char *stock_name = "AAPL";
    int quantity = 10;

    // Simulate a button click to buy stock
    buy_stock(stock_name, quantity);

    return 0;
}