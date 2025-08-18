#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void buy_function(const char *stock_name) {
    // Simulate buying a stock by printing the stock name
    printf("Buying stock: %s\n", stock_name);
}

void buy_stock(const char *stock_name, int quantity) {
    // Insert into database logic would go here
    // For demonstration, we'll just print the stock name and quantity
    printf("Inserting into database - Stock: %s, Quantity: %d\n", stock_name, quantity);

    // Call the buy_function with the stock name
    buy_function(stock_name);
}

int main() {
    const char *stock_name = "AAPL";
    int quantity = 10;

    // Simulate a form submission by calling buy_stock
    buy_stock(stock_name, quantity);

    return 0;
}