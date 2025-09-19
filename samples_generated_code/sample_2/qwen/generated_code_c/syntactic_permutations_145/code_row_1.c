#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database insert function
void insert_into_database(const char *stock_name, int quantity) {
    printf("Inserting %d of stock %s into the database.\n", quantity, stock_name);
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
    
    // Simulate a user clicking the buy button for AAPL stock
    buy_stock(stock_name, quantity);
    
    return 0;
}