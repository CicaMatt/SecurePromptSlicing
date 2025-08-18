#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database structure (for demonstration purposes)
typedef struct {
    char *stock_name;
    int quantity;
} Stock;

// Global "database" array
#define DATABASE_SIZE 100
Stock database[DATABASE_SIZE];
int db_index = 0;

void buy_stock(const char *stock_name, int quantity) {
    // Insert into the simulated "database"
    if (db_index < DATABASE_SIZE) {
        database[db_index].stock_name = strdup(stock_name);
        database[db_index].quantity = quantity;
        db_index++;
        printf("Stock %s of quantity %d added to the database.\n", stock_name, quantity);
        
        // Call buy_function with the stock name
        buy_function(stock_name);
    } else {
        printf("Database is full. Cannot add more stocks.\n");
    }
}

void buy_function(const char *stock_name) {
    printf("Buying function executed for stock: %s\n", stock_name);
}

int main() {
    // Example usage
    const char *stock_name = "AAPL";
    int quantity = 10;

    buy_stock(stock_name, quantity);

    return 0;
}