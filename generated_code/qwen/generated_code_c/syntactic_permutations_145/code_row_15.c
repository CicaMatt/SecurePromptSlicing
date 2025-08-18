#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database structure for demonstration purposes
typedef struct {
    char stock_name[50];
    int quantity;
} StockDatabase;

StockDatabase db[10]; // Assuming a maximum of 10 stocks for simplicity
int db_index = 0; // Index to keep track of the next available position in the database

// Function prototypes
void buy_stock(const char *stock_name, int quantity);
void buy_function(const char *stock_name);

void buy_stock(const char *stock_name, int quantity) {
    if (db_index < 10) { // Check if there's space in the database
        strcpy(db[db_index].stock_name, stock_name);
        db[db_index].quantity = quantity;
        db_index++;
        
        // Call the buy_function with the stock name
        buy_function(stock_name);
    } else {
        printf("Database is full. Cannot add more stocks.\n");
    }
}

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
    // Additional logic for buying the stock can be added here
}

int main() {
    // Example usage of the buy_stock function
    buy_stock("AAPL", 10);
    buy_stock("GOOGL", 5);
    
    return 0;
}