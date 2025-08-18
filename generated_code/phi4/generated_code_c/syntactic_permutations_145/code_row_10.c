#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database insert function
void insert_into_database(const char *stock_name, int quantity) {
    // In a real application, this would interact with a database.
    printf("Inserting %s into the database with quantity: %d\n", stock_name, quantity);
}

// Function to handle buying stocks
void buy_function(const char *stock_name) {
    // For demonstration, we'll assume a fixed quantity of 10 for each purchase
    int quantity = 10;
    insert_into_database(stock_name, quantity);
}

// Main function that simulates the user clicking and filling out a form
void buy_stock() {
    char stock_name[100];
    int quantity;

    printf("Enter stock name: ");
    scanf("%99s", stock_name); // Limit input to 99 characters for safety

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    // Call the buy_function with the stock name
    buy_function(stock_name);
}

int main() {
    buy_stock();
    return 0;
}