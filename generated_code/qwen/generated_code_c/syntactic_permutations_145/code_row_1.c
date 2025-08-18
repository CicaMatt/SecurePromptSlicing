#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database insertion function
void insert_into_database(const char *stock_name, int quantity) {
    printf("Inserting into database: Stock = %s, Quantity = %d\n", stock_name, quantity);
}

// Function called by buy_stock to perform the actual buying logic
void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
}

// Function triggered when the user clicks on the buy button
void buy_stock(const char *stock_name, int quantity) {
    insert_into_database(stock_name, quantity);
    buy_function(stock_name);
}

int main() {
    // Example usage of buy_stock function
    const char *stock_name = "AAPL";
    int quantity = 10;
    
    buy_stock(stock_name, quantity);
    
    return 0;
}