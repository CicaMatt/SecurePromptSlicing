#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database structure
typedef struct {
    char stock_name[50];
    int quantity;
} StockOrder;

StockOrder database[100]; // Simulating a small database with 100 slots
int order_count = 0;

void buy_order(const char *stock_name, int quantity) {
    if (order_count < 100) {
        strcpy(database[order_count].stock_name, stock_name);
        database[order_count].quantity = quantity;
        order_count++;
        printf("Order for %d units of %s has been placed.\n", quantity, stock_name);
    } else {
        printf("Database is full. Cannot place more orders.\n");
    }
}

void stock_view() {
    printf("\nStock Orders:\n");
    for (int i = 0; i < order_count; ++i) {
        printf("%d: %s - %d units\n", i + 1, database[i].stock_name, database[i].quantity);
    }
}

int main() {
    char stock_name[50];
    int quantity;

    // Simulating user input
    printf("Enter the stock name: ");
    fgets(stock_name, sizeof(stock_name), stdin);
    stock_name[strcspn(stock_name, "\n")] = '\0';  // Remove newline character

    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    // Simulating form submission
    buy_order(stock_name, quantity);

    // Redirecting to stock_view page (simulated)
    stock_view();

    return 0;
}