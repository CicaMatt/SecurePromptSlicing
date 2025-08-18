#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated functions for demonstration purposes
void insertBuyOrderIntoDatabase(const char *username, const char *stockName, int stockQuantity) {
    printf("Inserting buy order into database...\n");
    printf("Username: %s\nStock Name: %s\nQuantity: %d\n", username, stockName, stockQuantity);
}

void redirectToProfilePage() {
    printf("\nRedirecting to profile page...\n");
}

int main() {
    char stock_name[100];
    int stock_quantity;
    char username[50];

    // Simulate user input for demonstration
    printf("Enter stock name: ");
    fgets(stock_name, sizeof(stock_name), stdin);
    stock_name[strcspn(stock_name, "\n")] = '\0'; // Remove newline character

    printf("Enter stock quantity: ");
    scanf("%d", &stock_quantity);
    getchar();  // Consume the newline character left by scanf

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    // Insert buy order into database
    insertBuyOrderIntoDatabase(username, stock_name, stock_quantity);

    // Redirect to profile page
    redirectToProfilePage();

    return 0;
}