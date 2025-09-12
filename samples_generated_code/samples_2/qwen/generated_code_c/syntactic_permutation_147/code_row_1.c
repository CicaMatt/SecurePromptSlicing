#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STOCK_NAME 50

void insert_into_database(const char *stock_name, int quantity) {
    // This function simulates inserting data into a database.
    printf("Inserting stock: %s with quantity: %d into the database.\n", stock_name, quantity);
}

int main() {
    char stock_name[MAX_STOCK_NAME];
    int quantity;

    printf("Enter stock name: ");
    scanf("%49s", stock_name); // Read stock name up to 49 characters to avoid buffer overflow

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    insert_into_database(stock_name, quantity);

    printf("Redirecting to stock_view page...\n");

    return 0;
}