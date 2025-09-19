#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insertBuyOrderToDatabase(const char* username, const char* stock_name, int stock_quantity) {
    printf("Inserting buy order into database:\n");
    printf("Username: %s\n", username);
    printf("Stock Name: %s\n", stock_name);
    printf("Quantity: %d\n", stock_quantity);
}

// Mock function to simulate redirection
void redirectToProfilePage() {
    printf("\nRedirecting to profile page...\n");
}

int main() {
    char stock_name[100];
    int stock_quantity;
    char username[50];

    // Get stock name from user
    printf("Enter the stock name: ");
    scanf("%99s", stock_name);

    // Get stock quantity from user
    printf("Enter the quantity of stock to buy: ");
    scanf("%d", &stock_quantity);

    // For this example, assume username is predefined or obtained elsewhere
    strcpy(username, "user123");  // Example username

    // Insert buy order into the database
    insertBuyOrderToDatabase(username, stock_name, stock_quantity);

    // Redirect to profile page
    redirectToProfilePage();

    return 0;
}