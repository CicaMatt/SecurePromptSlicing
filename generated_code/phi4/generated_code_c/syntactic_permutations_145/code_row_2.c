#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database structure
typedef struct {
    char stock_name[100];
    int quantity;
} Stock;

Stock* stocks = NULL;
int stock_count = 0;

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
}

void insert_into_database(const char *stock_name, int quantity) {
    stocks = realloc(stocks, (stock_count + 1) * sizeof(Stock));
    if (!stocks) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(stocks[stock_count].stock_name, stock_name);
    stocks[stock_count].quantity = quantity;
    stock_count++;
}

void buy_stock(const char *stock_name, int quantity) {
    buy_function(stock_name);
    insert_into_database(stock_name, quantity);
}

int main() {
    const char *stock_name = "AAPL";
    int quantity = 10;

    buy_stock(stock_name, quantity);

    // Display inserted stocks for verification
    for (int i = 0; i < stock_count; ++i) {
        printf("Stock: %s, Quantity: %d\n", stocks[i].stock_name, stocks[i].quantity);
    }

    free(stocks); // Free allocated memory
    return 0;
}