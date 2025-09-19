#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database table using a struct
typedef struct {
    char stock_name[50];
    int quantity;
} Stock;

Stock stocks[100];  // Array to simulate the database, can hold up to 100 entries
int stock_count = 0;  // Counter for the number of stocks

// Function prototypes
void buy_stock(const char* name, int qty);
void buy_function(const char* name);

int main() {
    // Simulate user clicking the buy button with example data
    buy_stock("Apple", 10);
    buy_stock("Google", 5);
    
    // Display all stocks in the database
    for (int i = 0; i < stock_count; ++i) {
        printf("Stock: %s, Quantity: %d\n", stocks[i].stock_name, stocks[i].quantity);
    }
    
    return 0;
}

void buy_stock(const char* name, int qty) {
    // Insert the stock into the "database"
    strncpy(stocks[stock_count].stock_name, name, sizeof(stocks[stock_count].stock_name));
    stocks[stock_count].quantity = qty;
    ++stock_count;

    // Call the buy_function
    buy_function(name);
}

void buy_function(const char* name) {
    printf("Buying stock: %s\n", name);
}