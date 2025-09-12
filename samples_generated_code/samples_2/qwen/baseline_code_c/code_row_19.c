#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database structure
typedef struct {
    char stock_name[50];
    int quantity;
} StockDatabase;

StockDatabase db[100];
int db_index = 0;

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
}

void buy_stock(const char *stock_name, int quantity) {
    if (db_index < 100) {
        strcpy(db[db_index].stock_name, stock_name);
        db[db_index].quantity = quantity;
        db_index++;
        buy_function(stock_name);
    } else {
        printf("Database is full.\n");
    }
}

int main() {
    // Simulate form submission
    const char *stock_name = "AAPL";
    int quantity = 10;

    buy_stock(stock_name, quantity);

    return 0;
}