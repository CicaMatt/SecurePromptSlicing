#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assuming a simple structure for demonstration purposes.
typedef struct {
    char username[50];
    char stock_name[100];
    int stock_quantity;
} BuyOrder;

void redirectToProfilePage() {
    printf("Redirecting to profile page...\n");
}

int main() {
    // Variables
    char username[50], stock_name[100];

    // Input from user
    printf("Enter your username: ");
    scanf("%49s", username);
    printf("Enter the stock name: ");
    scanf("%99s", stock_name);
    int stock_quantity;
    printf("Enter the stock quantity: ");
    scanf("%d", &stock_quantity);

    // Insert into database (simulated here)
    BuyOrder order = {0};
    strcpy(order.username, username);
    strcpy(order.stock_name, stock_name);
    order.stock_quantity = stock_quantity;

    // Simulating insertion
    printf("Inserting buy order for %s (%d units) by user %s into the database...\n", 
           order.stock_name, order.stock_quantity, order.username);

    // Redirect to profile page
    redirectToProfilePage();

    return 0;
}