#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assuming a simple in-memory database for demonstration purposes.
typedef struct {
    char stock_name[50];
    int quantity;
} StockPurchase;

StockPurchase database[100]; // Simple array to simulate a database with 100 entries limit.
int db_count = 0;

void insert_into_database(const char *stock_name, int quantity) {
    if (db_count < 100) { // Ensure we do not overflow our simulated database
        strcpy(database[db_count].stock_name, stock_name);
        database[db_count].quantity = quantity;
        db_count++;
        printf("Inserted into database: %s, Quantity: %d\n", stock_name, quantity);
    } else {
        printf("Database is full!\n");
    }
}

void buy_function(const char *stock_name) {
    // This function could contain logic specific to buying a stock.
    printf("Buy function called with stock name: %s\n", stock_name);

    // Simulating purchase details
    int quantity = 10; // Example fixed quantity for this demonstration

    // Call the insert_into_database function to store the transaction
    insert_into_database(stock_name, quantity);
}

void buy_stock(const char *stock_name, int quantity) {
    printf("buy_stock called with stock name: %s, Quantity: %d\n", stock_name, quantity);

    // Call the buy_function and pass the stock name
    buy_function(stock_name);
}

int main() {
    const char *stock_name = "AAPL";
    int quantity = 5; // Example user input

    // Simulate a button click to trigger buying stocks
    buy_stock(stock_name, quantity);

    return 0;
}