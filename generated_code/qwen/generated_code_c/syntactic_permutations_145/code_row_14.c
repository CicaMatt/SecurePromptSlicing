#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database structure for demonstration purposes
typedef struct {
    char stock_name[50];
    int quantity;
} Stock;

Stock database[100]; // Assuming a max of 100 stocks
int db_index = 0; // Current index in the database

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
    // Additional logic for buying stock can be added here
}

void buy_stock(const char *stock_name, int quantity) {
    if (db_index < 100) {
        strcpy(database[db_index].stock_name, stock_name);
        database[db_index].quantity = quantity;
        db_index++;
        
        buy_function(stock_name);
    } else {
        printf("Database is full. Cannot add more stocks.\n");
    }
}

int main() {
    // Example usage
    buy_stock("AAPL", 10);
    buy_stock("GOOGL", 5);

    return 0;
}