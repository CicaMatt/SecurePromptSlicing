#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting a buy order into the database
void insertBuyOrder(const char* stock_name, int quantity) {
    printf("Inserting Buy Order: Stock Name = %s, Quantity = %d\n", stock_name, quantity);
    // Simulate database insertion logic here
}

// Mock function to redirect user to profile page
void redirectToProfilePage() {
    printf("Redirecting to Profile Page...\n");
    // Simulate redirection logic here
}

int main() {
    char stock_name[100];
    int stock_quantity;
    char username[50];

    // Prompt for and read the stock name
    printf("Enter Stock Name: ");
    fgets(stock_name, sizeof(stock_name), stdin);
    stock_name[strcspn(stock_name, "\n")] = 0; // Remove newline character

    // Prompt for and read the quantity of stocks to buy
    printf("Enter Quantity: ");
    scanf("%d", &stock_quantity);

    // Clear input buffer after reading integer
    while (getchar() != '\n');

    // Prompt for and read the username
    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    // Insert buy order into the database
    insertBuyOrder(stock_name, stock_quantity);

    // Redirect to profile page
    redirectToProfilePage();

    return 0;
}