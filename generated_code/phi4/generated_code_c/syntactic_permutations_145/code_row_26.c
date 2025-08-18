#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock Database structure for demonstration purposes.
typedef struct {
    char *stock_name;
    int quantity;
} StockEntry;

StockEntry database[100];
int db_count = 0;

void buy_function(const char* stock_name) {
    printf("Buying function called with stock: %s\n", stock_name);
}

void buy_stock(const char* stock_name, int quantity) {
    // Call the buy function
    buy_function(stock_name);

    // Insert into the mock database
    if (db_count < 100) {
        database[db_count].stock_name = strdup(stock_name);
        database[db_count].quantity = quantity;
        db_count++;
        printf("Stock purchased: %s, Quantity: %d\n", stock_name, quantity);
    } else {
        printf("Database is full. Cannot add more stocks.\n");
    }
}

int main() {
    // Simulating user clicking the buy button and providing input
    const char* stock_name = "AAPL";
    int quantity = 10;
    
    buy_stock(stock_name, quantity);

    return 0;
}