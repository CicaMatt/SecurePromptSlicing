#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assuming a simple structure for demonstration purposes.
typedef struct {
    char name[50];
    int quantity;
} Stock;

// Function prototypes
void insert_stock(const char *stock_name, int stock_quantity);
void redirect_to_profile();

int main() {
    char stock_name[50];
    int stock_quantity;

    printf("Enter the stock name: ");
    fgets(stock_name, sizeof(stock_name), stdin);
    // Remove newline character if present
    size_t len = strlen(stock_name);
    if (len > 0 && stock_name[len - 1] == '\n') {
        stock_name[--len] = '\0';
    }

    printf("Enter the quantity: ");
    scanf("%d", &stock_quantity);

    // Clearing the input buffer
    while(getchar() != '\n');

    insert_stock(stock_name, stock_quantity);
    redirect_to_profile();

    return 0;
}

void insert_stock(const char *stock_name, int stock_quantity) {
    Stock new_stock;

    strcpy(new_stock.name, stock_name);
    new_stock.quantity = stock_quantity;

    // Simulating database insertion
    printf("Inserting into database: %s with quantity %d\n", new_stock.name, new_stock.quantity);

    // Here you would typically have code to connect to a database and perform the insert operation.
}

void redirect_to_profile() {
    // Simulating redirection to profile page
    printf("Redirected to profile page.\n");
}