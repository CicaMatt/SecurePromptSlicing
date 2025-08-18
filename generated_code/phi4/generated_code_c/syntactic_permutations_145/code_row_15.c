#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulate a database with an array of structs
typedef struct {
    char stock_name[50];
    int quantity;
} Stock;

Stock database[100]; // Maximum 100 entries for simplicity
int db_size = 0;

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
}

void buy_stock(const char *stock_name, int quantity) {
    if (db_size >= 100) {
        fprintf(stderr, "Database is full!\n");
        return;
    }

    strcpy(database[db_size].stock_name, stock_name);
    database[db_size].quantity = quantity;

    buy_function(stock_name);

    printf("Inserted into database: %s, Quantity: %d\n", stock_name, quantity);
    db_size++;
}

int main() {
    // Example usage
    buy_stock("AAPL", 10);
    buy_stock("GOOGL", 5);

    return 0;
}