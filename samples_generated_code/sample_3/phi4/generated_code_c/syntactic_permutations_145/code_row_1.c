#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock structure to simulate a database table row.
typedef struct {
    char stock_name[50];
    int quantity;
} StockEntry;

// Simulated database represented as an array of StockEntry structs.
#define MAX_STOCKS 100
StockEntry stocks_db[MAX_STOCKS];
int num_stocks = 0;

void buy_function(const char *stock_name) {
    // This function performs some operations with the stock name.
    printf("Buying stock: %s\n", stock_name);
}

void insert_into_database(StockEntry entry) {
    if (num_stocks < MAX_STOCKS) {
        stocks_db[num_stocks++] = entry;
        printf("Inserted into database: Stock Name - %s, Quantity - %d\n",
               entry.stock_name, entry.quantity);
    } else {
        printf("Database is full. Cannot insert more entries.\n");
    }
}

void buy_stock(const char *stock_name, int quantity) {
    // Call the buy_function with stock name.
    buy_function(stock_name);

    // Create an entry for the database insertion.
    StockEntry new_entry;
    strncpy(new_entry.stock_name, stock_name, sizeof(new_entry.stock_name) - 1);
    new_entry.quantity = quantity;

    // Insert into simulated database.
    insert_into_database(new_entry);
}

int main() {
    // Simulate user clicking buy button for certain stocks.
    buy_stock("AAPL", 10);
    buy_stock("GOOGL", 5);

    return 0;
}