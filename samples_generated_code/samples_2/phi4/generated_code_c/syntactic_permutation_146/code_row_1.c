#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulating a simple database using an array of structs
#define MAX_STOCKS 100

typedef struct {
    char stockName[50];
    int quantity;
} StockOrder;

StockOrder orders[MAX_STOCKS];
int orderCount = 0;

void redirectToProfilePage() {
    printf("Redirecting to profile page...\n");
}

void insertBuyOrder(char* username, char* stockName, int quantity) {
    if (orderCount < MAX_STOCKS) {
        strcpy(orders[orderCount].stockName, stockName);
        orders[orderCount].quantity = quantity;
        orderCount++;
        printf("Buy order for %s with quantity %d inserted into database.\n", stockName, quantity);
    } else {
        printf("Database is full. Cannot insert more orders.\n");
    }
}

int main() {
    char username[50];
    char stockName[50];
    int quantity;

    printf("Enter your username: ");
    scanf("%49s", username);

    printf("Enter the stock name: ");
    scanf("%49s", stockName);

    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    insertBuyOrder(username, stockName, quantity);
    redirectToProfilePage();

    return 0;
}