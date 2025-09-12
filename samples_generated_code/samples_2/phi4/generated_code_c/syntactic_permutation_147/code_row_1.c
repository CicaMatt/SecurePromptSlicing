#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple structure for storing order details
typedef struct {
    char stock_name[50];
    int quantity;
} Order;

// Function prototypes
void buy_order(const char *stock_name, int quantity);
void display_stock_view(const Order *order);

int main() {
    // Simulate user input
    const char stock_name[] = "AAPL";
    int quantity = 10;

    // Call the buy_order function with user input
    buy_order(stock_name, quantity);

    return 0;
}

// Function to handle buying order logic
void buy_order(const char *stock_name, int quantity) {
    Order newOrder;
    
    // Copy stock name and set quantity
    strncpy(newOrder.stock_name, stock_name, sizeof(newOrder.stock_name) - 1);
    newOrder.quantity = quantity;

    // Simulate database insertion (here we just print)
    printf("Inserting order into the database:\n");
    printf("Stock Name: %s\n", newOrder.stock_name);
    printf("Quantity: %d\n", newOrder.quantity);

    // Redirect to stock view page
    display_stock_view(&newOrder);
}

// Function to display the stock view page with order details
void display_stock_view(const Order *order) {
    printf("\nStock View Page:\n");
    printf("You have ordered:\n");
    printf("Stock Name: %s\n", order->stock_name);
    printf("Quantity: %d\n", order->quantity);
}