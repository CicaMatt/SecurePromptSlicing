#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to represent StockOrder.
typedef struct {
    char stockName[100];
    int quantity;
} StockOrder;

// Function prototypes
void buy_order(StockOrder order);
void insert_into_database(const StockOrder* order);

int main() {
    // Simulate user input form submission
    StockOrder order;
    
    printf("Enter the stock name: ");
    scanf("%99s", order.stockName);  // Limit to prevent buffer overflow
    
    printf("Enter the quantity: ");
    scanf("%d", &order.quantity);
    
    // Call buy_order function with the entered data
    buy_order(order);

    return 0;
}

// Function to handle buying orders
void buy_order(StockOrder order) {
    // Insert the order into the database (simulation)
    insert_into_database(&order);
    
    // Redirect user to stock_view page (simulation)
    printf("\nRedirecting to stock_view page...\n");
    printf("Successfully added %s with quantity %d\n", order.stockName, order.quantity);
}

// Function to simulate inserting data into a database
void insert_into_database(const StockOrder* order) {
    // For demonstration purposes, just print the data being inserted
    printf("Inserting into database:\n");
    printf("Stock Name: %s\nQuantity: %d\n", order->stockName, order->quantity);

    // In a real application, here you'd write code to insert the record into an actual database.
}