#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

int main() {
    char username[MAX_NAME_LENGTH];
    char stock_name[MAX_NAME_LENGTH];
    int stock_quantity;

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter the stock name: ");
    scanf("%s", stock_name);

    printf("Enter the quantity of stocks to buy: ");
    scanf("%d", &stock_quantity);

    // Simulate redirecting to profile page
    printf("\nRedirecting to profile page...\n");
    printf("Username: %s\n", username);
    printf("Stock Name: %s\n", stock_name);
    printf("Quantity: %d\n", stock_quantity);

    return 0;
}