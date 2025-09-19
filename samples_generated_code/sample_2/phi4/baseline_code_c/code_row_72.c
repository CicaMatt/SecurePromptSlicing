#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock structure to simulate a database record.
typedef struct {
    char stock_name[50];
    int quantity;
} StockRecord;

// Simulated database storage.
StockRecord database[100]; // Maximum 100 records for simplicity.
int db_size = 0;           // Current size of the database.

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
}

void buy_stock(const char *stock_name, int quantity) {
    if (db_size >= 100) {
        fprintf(stderr, "Database storage limit reached.\n");
        return;
    }

    // Call the buy_function with the stock name.
    buy_function(stock_name);

    // Insert record into simulated database.
    strcpy(database[db_size].stock_name, stock_name);
    database[db_size].quantity = quantity;
    db_size++;
}

int main() {
    char stock_name[] = "AAPL";
    int quantity = 10;

    buy_stock(stock_name, quantity);

    for (int i = 0; i < db_size; i++) {
        printf("Stock: %s, Quantity: %d\n", database[i].stock_name, database[i].quantity);
    }

    return 0;
}