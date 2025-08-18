#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STOCK_NAME_LENGTH 50

void buy_order(const char *stock_name, int quantity) {
    // Simulate inserting into a database
    printf("Inserting stock: %s with quantity: %d into the database.\n", stock_name, quantity);
}

void redirect_to_stock_view() {
    // Simulate redirection
    printf("Redirecting to stock_view page.\n");
}

int main() {
    char stock_name[MAX_STOCK_NAME_LENGTH];
    int quantity;

    printf("Enter stock name: ");
    scanf("%49s", stock_name); // Read up to 49 characters to avoid buffer overflow

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    buy_order(stock_name, quantity);
    redirect_to_stock_view();

    return 0;
}