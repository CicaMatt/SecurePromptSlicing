#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulating a database with a simple structure
typedef struct {
    char stockName[50];
    int quantity;
} StockOrder;

StockOrder ordersDatabase[100]; // Simple database array to store orders.
int orderCount = 0;             // Counter for the number of stored orders.

void buy_stock(const char *stockName, int quantity) {
    if (orderCount < sizeof(ordersDatabase) / sizeof(ordersDatabase[0])) {
        strcpy(ordersDatabase[orderCount].stockName, stockName);
        ordersDatabase[orderCount].quantity = quantity;
        orderCount++;
        
        // Call buy_function
        buy_function(stockName);

        printf("Stock %s of quantity %d bought and recorded.\n", stockName, quantity);
    } else {
        printf("Order limit reached. Cannot record more orders.\n");
    }
}

void buy_function(const char *stockName) {
    printf("Processing purchase for stock: %s\n", stockName);
}

int main() {
    // Example usage
    buy_stock("AAPL", 10);
    buy_stock("GOOG", 5);

    return 0;
}