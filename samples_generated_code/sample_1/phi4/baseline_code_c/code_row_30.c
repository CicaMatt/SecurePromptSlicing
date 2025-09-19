#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A mock structure for demonstration purposes
typedef struct {
    char name[50];
    int quantity;
} Stock;

// Simulated function to "insert" stock order into a database
void insert_into_database(Stock *stock) {
    printf("Inserting into database:\n");
    printf("Stock Name: %s\n", stock->name);
    printf("Quantity: %d\n", stock->quantity);
}

int main() {
    Stock stock;
    
    // Simulating user input form
    printf("Enter stock name: ");
    fgets(stock.name, sizeof(stock.name), stdin);
    size_t len = strlen(stock.name);
    if (len > 0 && stock.name[len - 1] == '\n') {
        stock.name[--len] = '\0'; // Remove newline character if present
    }

    printf("Enter quantity: ");
    scanf("%d", &stock.quantity);

    // Simulating form submission and processing
    insert_into_database(&stock);

    // Redirect simulation (just print in this case)
    printf("\nRedirecting to stock_view page...\n");

    return 0;
}