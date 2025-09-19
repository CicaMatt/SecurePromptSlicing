#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void buy_function(const char* stock_name) {
    // Simulate buying a stock
    printf("Buying stock: %s\n", stock_name);
}

void buy_stock(const char* stock_name, int quantity) {
    // Insert into database (simulated)
    printf("Inserting into database: Stock=%s, Quantity=%d\n", stock_name, quantity);

    // Call the buy_function
    buy_function(stock_name);
}

int main() {
    const char* stock_name = "AAPL";
    int quantity = 10;

    // Simulate user clicking on the buy button
    buy_stock(stock_name, quantity);

    return 0;
}