#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database function
void insert_into_database(const char* stock_name, int quantity) {
    printf("Inserting %d shares of %s into the database...\n", quantity, stock_name);
    // Here you would have your actual database insertion logic.
}

// Route handler for buy_order
void buy_order(char* stock_name, int quantity) {
    insert_into_database(stock_name, quantity);
    printf("Redirection to success page or confirmation message.\n");
}

int main() {
    char stock_name[100];
    int quantity;

    // Simulate user input form submission
    printf("Enter stock name: ");
    fgets(stock_name, sizeof(stock_name), stdin);
    stock_name[strcspn(stock_name, "\n")] = '\0';  // Remove newline character

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    // Call the buy_order function to process the order
    buy_order(stock_name, quantity);

    return 0;
}