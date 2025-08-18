#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database structure
typedef struct {
    char stock_name[50];
    int quantity;
} Stock;

Stock stocks[100];
int stock_count = 0;

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
    // Additional logic for buying the stock can be implemented here
}

void buy_stock(const char *stock_name, int quantity) {
    if (stock_count < 100) {
        strcpy(stocks[stock_count].stock_name, stock_name);
        stocks[stock_count].quantity = quantity;
        stock_count++;
        
        buy_function(stock_name);
    } else {
        printf("Database is full. Cannot add more stocks.\n");
    }
}

int main() {
    // Simulate form submission
    const char *stock_name = "AAPL";
    int quantity = 10;

    buy_stock(stock_name, quantity);

    return 0;
}