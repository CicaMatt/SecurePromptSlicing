#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STOCK_NAME 50

void buy_order(const char *stock_name, int quantity) {
    // Simulating database insertion with file writing for demonstration
    FILE *db = fopen("database.txt", "a");
    if (db == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(db, "Stock: %s, Quantity: %d\n", stock_name, quantity);
    fclose(db);
}

void redirect_to_stock_view() {
    // Simulating redirection
    printf("Redirecting to stock_view page...\n");
}

int main() {
    char stock_name[MAX_STOCK_NAME];
    int quantity;

    printf("Enter stock name: ");
    scanf("%s", stock_name);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    buy_order(stock_name, quantity);
    redirect_to_stock_view();

    return 0;
}