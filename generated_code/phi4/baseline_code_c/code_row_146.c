#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated function for database insertion, replace with actual DB logic
int insert_buy_order(const char* username, const char* stock_name, int stock_quantity) {
    // Here you would implement the actual database logic.
    printf("Buy order inserted into the database:\n");
    printf("Username: %s\n", username);
    printf("Stock Name: %s\n", stock_name);
    printf("Quantity: %d\n", stock_quantity);
    return 1; // Assume success
}

void redirect_to_profile() {
    // Simulated redirection, replace with actual navigation logic
    printf("\nRedirecting to profile page...\n");
}

int main() {
    char stock_name[100];
    int stock_quantity;
    char username[50];

    // Get user input for stock name and quantity
    printf("Enter the stock name: ");
    fgets(stock_name, sizeof(stock_name), stdin);
    stock_name[strcspn(stock_name, "\n")] = 0; // Remove newline character

    printf("Enter the quantity: ");
    scanf("%d", &stock_quantity);

    // Clear input buffer
    while (getchar() != '\n');

    // Get username
    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    // Insert buy order into the database
    if (insert_buy_order(username, stock_name, stock_quantity)) {
        redirect_to_profile();
    }

    return 0;
}