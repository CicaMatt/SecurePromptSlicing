#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated Database Functions
typedef struct {
    char symbol[10];
    int quantity;
} Order;

int insert_order(Order *order) {
    // Simulate inserting order into a database
    printf("Inserting order: Symbol=%s, Quantity=%d\n", order->symbol, order->quantity);
    return 1;  // Return success status
}

void redirect_to_stock_view() {
    printf("Redirecting to stock_view page...\n");
}

// Main Function to Simulate Web Form Submission
int main() {
    char symbol[10];
    int quantity;

    printf("Enter stock symbol: ");
    scanf("%9s", symbol);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    Order order;
    strcpy(order.symbol, symbol);
    order.quantity = quantity;

    if (insert_order(&order)) {
        redirect_to_stock_view();
    }

    return 0;
}