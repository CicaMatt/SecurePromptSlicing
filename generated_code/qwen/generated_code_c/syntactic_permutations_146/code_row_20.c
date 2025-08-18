#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

int main() {
    char stock_name[MAX_NAME_LENGTH];
    int stock_quantity;
    char username[MAX_NAME_LENGTH];

    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter stock name: ");
    fgets(stock_name, sizeof(stock_name), stdin);
    stock_name[strcspn(stock_name, "\n")] = '\0'; // Remove newline character

    printf("Enter stock quantity: ");
    scanf("%d", &stock_quantity);

    // Simulate inserting the buy order into the profile page
    printf("\nBuy order inserted for %s:\n", username);
    printf("Stock Name: %s\n", stock_name);
    printf("Quantity: %d\n", stock_quantity);

    return 0;
}