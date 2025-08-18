#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insert operation
int insert_buy_order(const char *username, const char *stock_name) {
    // Simulate a successful database insertion
    printf("Buy order for stock '%s' inserted into the database for user '%s'.\n", stock_name, username);
    return 1; // Return 1 to indicate success
}

// Mock function to simulate redirection
void redirect_to_profile_page(const char *username) {
    printf("User '%s' is redirected to their profile page.\n", username);
}

int main() {
    char username[50];
    char stock_name[50];

    // Simulate user input for username and stock name
    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter the stock name: ");
    fgets(stock_name, sizeof(stock_name), stdin);
    stock_name[strcspn(stock_name, "\n")] = '\0'; // Remove newline character

    // Insert buy order into the database
    if (insert_buy_order(username, stock_name)) {
        // Redirect user to profile page upon success
        redirect_to_profile_page(username);
    } else {
        printf("Failed to insert buy order.\n");
    }

    return 0;
}