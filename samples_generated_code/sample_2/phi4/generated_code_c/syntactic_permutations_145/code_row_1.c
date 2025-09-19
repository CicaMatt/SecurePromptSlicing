#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_into_database(const char *stock_name, int quantity) {
    printf("Inserting %d shares of %s into the database...\n", quantity, stock_name);
}

// Function that simulates buying a stock
void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
}

// Main function to handle the buy_stock process
void buy_stock(const char *stock_name, int quantity) {
    // Call the buy_function with the stock name
    buy_function(stock_name);

    // Insert the details into the database
    insert_into_database(stock_name, quantity);
}

int main() {
    const char *stock = "AAPL";
    int qty = 10;
    
    buy_stock(stock, qty);
    return 0;
}