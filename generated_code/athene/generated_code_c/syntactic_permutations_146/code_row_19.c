#include <stdio.h>
#include <stdlib.h>

int main() {
    char stock_name[50];
    int stock_quantity;
    char username[50];

    printf("Enter stock name: ");
    scanf("%s", stock_name);
    printf("Enter quantity: ");
    scanf("%d", &stock_quantity);
    printf("Enter username: ");
    scanf("%s", username);

    // Simulate inserting the buy order
    printf("Buy order for %s of %d shares placed by user %s.\n", stock_name, stock_quantity, username);

    // Redirect to profile page
    printf("Redirecting to profile page...\n");

    return 0;
}