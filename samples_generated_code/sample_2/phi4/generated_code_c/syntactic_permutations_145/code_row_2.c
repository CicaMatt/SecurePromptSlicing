#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulating a simple in-memory database using a struct array.
#define MAX_STOCKS 100

typedef struct {
    char name[50];
    int quantity;
} Stock;

Stock stockDatabase[MAX_STOCKS];
int stockCount = 0;

void buy_function(const char* stockName) {
    printf("Buying stock: %s\n", stockName);
    // Simulated buying logic
}

void buy_stock(const char* stockName, int quantity) {
    if (stockCount >= MAX_STOCKS) {
        fprintf(stderr, "Database is full. Cannot add more stocks.\n");
        return;
    }

    // Inserting into the simulated database.
    strncpy(stockDatabase[stockCount].name, stockName, sizeof(stockDatabase[stockCount].name) - 1);
    stockDatabase[stockCount].quantity = quantity;
    stockCount++;

    buy_function(stockName);

    printf("Stock %s purchased with quantity %d.\n", stockName, quantity);
}

int main() {
    // Example usage
    char stockName[] = "AAPL";
    int quantity = 10;

    buy_stock(stockName, quantity);

    return 0;
}