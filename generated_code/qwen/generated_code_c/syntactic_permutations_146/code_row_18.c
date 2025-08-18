#include <stdio.h>
#include <stdlib.h>

int main() {
    char stock_name[50];
    int stock_quantity;
    char username[50];

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter stock name: ");
    scanf("%s", stock_name);

    printf("Enter quantity: ");
    scanf("%d", &stock_quantity);

    // Simulating redirection to profile page
    printf("\nRedirecting to profile page...\n");
    printf("Username: %s\n", username);
    printf("Stock Name: %s\n", stock_name);
    printf("Stock Quantity: %d\n", stock_quantity);

    return 0;
}