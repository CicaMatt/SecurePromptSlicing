#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulating a simple database structure for demonstration purposes
typedef struct {
    char stockName[50];
    int quantity;
} Stock;

Stock database[100]; // Assuming a maximum of 100 stocks for simplicity
int stockCount = 0;

void buy_function(const char *stockName) {
    printf("Buying stock: %s\n", stockName);
    // Additional logic to handle buying the stock can be added here
}

void buy_stock(const char *stockName, int quantity) {
    if (stockCount >= 100) {
        printf("Database is full. Cannot add more stocks.\n");
        return;
    }
    
    strcpy(database[stockCount].stockName, stockName);
    database[stockCount].quantity = quantity;
    stockCount++;
    
    buy_function(stockName);
}

int main() {
    // Example usage of the buy_stock function
    const char *stockName = "AAPL";
    int quantity = 10;
    
    buy_stock(stockName, quantity);
    
    return 0;
}