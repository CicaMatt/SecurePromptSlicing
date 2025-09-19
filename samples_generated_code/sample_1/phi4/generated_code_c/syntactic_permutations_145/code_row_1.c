#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to represent a stock entry in the database.
typedef struct {
    char stock_name[50];
    int quantity;
} Stock;

// Mock function to simulate buying action for a given stock name.
void buy_function(const char *stock_name) {
    printf("Buying %s...\n", stock_name);
    // Simulate some processing time.
    sleep(1);
    printf("%s purchased successfully.\n", stock_name);
}

// Function to insert stock information into the database.
void insert_into_database(const Stock *stock_entry) {
    // In a real application, this would involve SQL commands or other DB operations.
    printf("Inserting into database: %s, Quantity: %d\n", stock_entry->stock_name, stock_entry->quantity);
}

// Function called when the user clicks on the buy button.
void buy_stock(const char *stock_name, int quantity) {
    Stock new_stock;
    strcpy(new_stock.stock_name, stock_name);
    new_stock.quantity = quantity;

    // Call the function to simulate buying process for the given stock name.
    buy_function(stock_name);

    // Insert the stock information into the database.
    insert_into_database(&new_stock);
}

int main() {
    // Example usage of the buy_stock function.
    char stock_name[] = "AAPL";
    int quantity = 10;

    buy_stock(stock_name, quantity);

    return 0;
}