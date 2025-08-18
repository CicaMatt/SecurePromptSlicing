#include <stdio.h>
#include <stdlib.h>

int main() {
    char stockName[100];
    int quantity;

    printf("Enter the stock name: ");
    scanf("%99s", stockName);
    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    // Simulate storing data and redirecting to profile page
    printf("Stock Name: %s\nQuantity: %d\n", stockName, quantity);
    printf("Redirecting to profile page...\n");

    return 0;
}