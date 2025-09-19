#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulating a simple database insertion
void insert_into_database(const char *stock_name, int quantity) {
    printf("Inserting into database: Stock = %s, Quantity = %d\n", stock_name, quantity);
}

// Function to simulate buying a stock
void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
}

// Function called when the user clicks on the buy button
void buy_stock(const char *stock_name, int quantity) {
    insert_into_database(stock_name, quantity);
    buy_function(stock_name);
}

int main() {
    const char *stock_name = "AAPL";
    int quantity = 10;
    
    // Simulating a user clicking the buy button for AAPL stock with a quantity of 10
    buy_stock(stock_name, quantity);
    
    return 0;
}