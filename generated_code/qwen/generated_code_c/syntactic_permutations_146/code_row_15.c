#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STOCK_NAME 100

int main() {
    char stock_name[MAX_STOCK_NAME];
    int stock_quantity;
    char username[50];

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter the stock name: ");
    scanf("%s", stock_name);

    printf("Enter the quantity: ");
    scanf("%d", &stock_quantity);

    // Simulate database insertion
    printf("\nInserting into database:\n");
    printf("Username: %s\n", username);
    printf("Stock Name: %s\n", stock_name);
    printf("Quantity: %d\n", stock_quantity);

    // Redirect to profile page simulation
    printf("\nRedirecting to profile page...\n");

    return 0;
}