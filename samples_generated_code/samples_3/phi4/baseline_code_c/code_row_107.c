#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulate a database with an array of structs
#define MAX_ORDERS 100

typedef struct {
    char stock_name[50];
    int stock_quantity;
    char username[50];
} StockOrder;

StockOrder orders[MAX_ORDERS];
int order_count = 0;

void insert_order(const char *stock_name, int stock_quantity, const char *username) {
    if (order_count < MAX_ORDERS) {
        strcpy(orders[order_count].stock_name, stock_name);
        orders[order_count].stock_quantity = stock_quantity;
        strcpy(orders[order_count].username, username);
        order_count++;
    } else {
        printf("Order limit reached!\n");
    }
}

void redirect_to_profile(const char *username) {
    printf("Redirecting %s to profile page...\n", username);
}

int main() {
    char stock_name[50];
    int stock_quantity;
    char username[50];

    // Simulate user input
    printf("Enter stock name: ");
    scanf("%49s", stock_name);

    printf("Enter quantity: ");
    scanf("%d", &stock_quantity);

    printf("Enter username: ");
    scanf("%49s", username);

    insert_order(stock_name, stock_quantity, username);
    redirect_to_profile(username);

    return 0;
}