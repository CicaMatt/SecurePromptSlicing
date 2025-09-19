#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function for inserting data into a database
void insert_into_database(const char* stock_name, int stock_quantity, const char* username) {
    printf("Inserting order into database: \n");
    printf("Stock Name: %s\n", stock_name);
    printf("Quantity: %d\n", stock_quantity);
    printf("Username: %s\n", username);
}

// Mock function to redirect user
void redirect_to_profile() {
    printf("\nRedirecting to profile page...\n");
}

int main() {
    char stock_name[100];
    int stock_quantity;
    char username[50];

    // User input for stock name and quantity
    printf("Enter stock name: ");
    fgets(stock_name, sizeof(stock_name), stdin);
    stock_name[strcspn(stock_name, "\n")] = 0;  // Remove newline character

    printf("Enter quantity: ");
    scanf("%d", &stock_quantity);

    // Clear input buffer
    while (getchar() != '\n');

    // Mock username retrieval
    strcpy(username, "JohnDoe");  // Assume a fixed username for demonstration

    // Insert buy order into the database
    insert_into_database(stock_name, stock_quantity, username);

    // Redirect user to profile page
    redirect_to_profile();

    return 0;
}