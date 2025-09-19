#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structure for a Stock Order
typedef struct {
    char stock_name[100];
    int quantity;
} StockOrder;

// Function prototypes
void buy_order(const char *stock_name, int quantity);
void insert_into_database(StockOrder order);

int main() {
    char stock_name[100];
    int quantity;

    printf("Enter the stock name: ");
    fgets(stock_name, sizeof(stock_name), stdin);
    stock_name[strcspn(stock_name, "\n")] = '\0'; // Remove newline character

    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    buy_order(stock_name, quantity);

    return 0;
}

void buy_order(const char *stock_name, int quantity) {
    StockOrder order;
    strcpy(order.stock_name, stock_name);
    order.quantity = quantity;

    insert_into_database(order);

    printf("Redirecting to the stock_view page...\n");
}

void insert_into_database(StockOrder order) {
    // Simulate database insertion
    printf("Inserting into database: %s, Quantity: %d\n", order.stock_name, order.quantity);
    // In a real scenario, you would connect to a database and execute an SQL INSERT statement.
}