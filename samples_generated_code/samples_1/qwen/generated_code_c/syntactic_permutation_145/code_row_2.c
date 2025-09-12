#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database insertion function
void insert_into_database(const char *stock_name, int quantity) {
    printf("Inserting %d of %s into database\n", quantity, stock_name);
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

    buy_stock(stock_name, quantity);

    return 0;
}