#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char stockName[50];
    int quantity;
} Stock;

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
    // Simulate database insertion here
}

int insert_into_database(Stock stock) {
    printf("Inserting into database: %s, Quantity: %d\n", stock.stockName, stock.quantity);
    return 1; // Return success status (1)
}

void buy_stock(const char *stock_name, int quantity) {
    Stock stock;
    strncpy(stock.stockName, stock_name, sizeof(stock.stockName));
    stock.quantity = quantity;

    if (insert_into_database(stock)) {
        buy_function(stock_name);
    } else {
        printf("Failed to insert into database.\n");
    }
}

int main() {
    const char *stock_name = "AAPL";
    int quantity = 10;
    
    buy_stock(stock_name, quantity);

    return 0;
}