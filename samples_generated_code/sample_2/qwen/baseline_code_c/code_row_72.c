#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database functions for demonstration purposes
void insert_into_database(const char* stock_name, int quantity) {
    printf("Inserting %d units of %s into the database.\n", quantity, stock_name);
}

void buy_function(const char* stock_name) {
    printf("Buying stock: %s\n", stock_name);
}

void buy_stock(const char* stock_name, int quantity) {
    insert_into_database(stock_name, quantity);
    buy_function(stock_name);
}

int main() {
    // Simulating form input
    const char* stock_name = "AAPL";
    int quantity = 10;

    // Calling the buy_stock function as if the user clicked the buy button
    buy_stock(stock_name, quantity);

    return 0;
}