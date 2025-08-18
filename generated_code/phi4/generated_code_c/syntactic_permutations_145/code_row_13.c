#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database structure for demonstration purposes
typedef struct {
    char stock_name[100];
} Stock;

Stock database[10]; // Simulate a small fixed-size database
int db_size = 0;    // Track the number of entries

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
}

void buy_stock(const char *stock_name) {
    if (db_size >= sizeof(database) / sizeof(Stock)) {
        printf("Database is full, cannot insert new stock.\n");
        return;
    }

    // Call the buy_function
    buy_function(stock_name);

    // Insert into the simulated database
    strncpy(database[db_size].stock_name, stock_name, sizeof(database[db_size].stock_name) - 1);
    database[db_size].stock_name[sizeof(database[db_size].stock_name) - 1] = '\0';
    db_size++;

    printf("Stock '%s' inserted into the database.\n", stock_name);
}

int main() {
    buy_stock("AAPL");
    buy_stock("GOOGL");
    return 0;
}