#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to simulate database insertion (for demonstration purposes)
void insertBuyOrder(const char *username, const char *stock_name, int stock_quantity) {
    printf("Inserting buy order into the database...\n");
    printf("Username: %s\n", username);
    printf("Stock Name: %s\n", stock_name);
    printf("Quantity: %d\n", stock_quantity);
    // Here you would add actual database insertion code
}

// Function to redirect user (simulated)
void redirectToUser() {
    printf("Redirecting user...\n");
    // Simulating a redirection by printing a message or using system commands
    // In real applications, this could involve sending an HTTP response in web apps
}

int main() {
    char stock_name[100];
    int stock_quantity;
    char username[50];

    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0'; // Remove newline character
    }

    printf("Enter stock name: ");
    fgets(stock_name, sizeof(stock_name), stdin);
    len = strlen(stock_name);
    if (len > 0 && stock_name[len - 1] == '\n') {
        stock_name[--len] = '\0'; // Remove newline character
    }

    printf("Enter stock quantity: ");
    scanf("%d", &stock_quantity);

    insertBuyOrder(username, stock_name, stock_quantity);
    redirectToUser();

    return 0;
}