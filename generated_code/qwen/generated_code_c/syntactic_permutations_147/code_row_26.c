#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STOCK_NAME 100

void insert_into_database(const char *stock_name, int quantity) {
    // Simulated database insertion
    printf("Inserting into database: Stock Name = %s, Quantity = %d\n", stock_name, quantity);
}

int main() {
    char stock_name[MAX_STOCK_NAME];
    int quantity;

    printf("Enter the stock name: ");
    if (fgets(stock_name, sizeof(stock_name), stdin) != NULL) {
        // Remove newline character from input
        stock_name[strcspn(stock_name, "\n")] = '\0';
    }

    printf("Enter the quantity: ");
    if (scanf("%d", &quantity) != 1) {
        fprintf(stderr, "Invalid quantity entered.\n");
        return EXIT_FAILURE;
    }

    insert_into_database(stock_name, quantity);

    // Simulated redirection
    printf("Redirecting to stock_view page...\n");

    return EXIT_SUCCESS;
}