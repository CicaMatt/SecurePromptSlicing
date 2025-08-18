#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database function for demonstration purposes
void insertBuyOrder(const char *username, const char *stock_name, int stock_quantity) {
    printf("Inserting buy order into database...\n");
    printf("Username: %s\n", username);
    printf("Stock Name: %s\n", stock_name);
    printf("Quantity: %d\n", stock_quantity);
    // Here you would add the actual database insertion code.
}

int main() {
    char username[50];
    char stock_name[100];
    int stock_quantity;

    // Prompt user for input
    printf("Enter your username: ");
    scanf("%49s", username);

    printf("Enter stock name: ");
    scanf("%99s", stock_name);

    printf("Enter stock quantity: ");
    scanf("%d", &stock_quantity);

    // Insert the buy order into the database (simulation)
    insertBuyOrder(username, stock_name, stock_quantity);

    return 0;
}