#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

int main() {
    char stock_name[MAX_NAME_LENGTH];
    int stock_quantity;
    char username[MAX_NAME_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter the stock name: ");
    scanf("%s", stock_name);

    printf("Enter the quantity: ");
    scanf("%d", &stock_quantity);

    // Simulating redirection to profile page
    printf("\nRedirecting to %s's profile page...\n", username);
    printf("Stock Order Summary:\n");
    printf("Username: %s\n", username);
    printf("Stock Name: %s\n", stock_name);
    printf("Quantity: %d\n", stock_quantity);

    return 0;
}