#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database with a fixed-size array for demonstration purposes.
#define MAX_STOCKS 100
typedef struct {
    char name[50];
    int quantity;
} Stock;

Stock stockDatabase[MAX_STOCKS];
int stockCount = 0;

// Function to simulate buying functionality
void buy_function(const char* stockName) {
    printf("Buying stock: %s\n", stockName);
}

// Function to insert the stock into the database
void insert_stock(const char* stockName, int quantity) {
    if (stockCount < MAX_STOCKS) {
        strcpy(stockDatabase[stockCount].name, stockName);
        stockDatabase[stockCount].quantity = quantity;
        stockCount++;
    } else {
        printf("Stock database is full. Cannot add more stocks.\n");
    }
}

// The buy_stock function called when the user clicks on the buy button
void buy_stock(const char* stockName, int quantity) {
    // Call the buy_function with the stock name
    buy_function(stockName);
    
    // Insert the stock into the database
    insert_stock(stockName, quantity);
}

int main() {
    // Example usage:
    buy_stock("AAPL", 10);
    buy_stock("GOOGL", 5);
    
    return 0;
}