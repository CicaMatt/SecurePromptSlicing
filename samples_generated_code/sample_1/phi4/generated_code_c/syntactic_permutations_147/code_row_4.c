#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated Database Functionality
typedef struct {
    char *stock_name;
    int quantity;
} Order;

#define MAX_ORDERS 100

Order orders[MAX_ORDERS];
int order_count = 0;

void insert_order(char *name, int qty) {
    if (order_count >= MAX_ORDERS) {
        printf("Database is full. Cannot add more orders.\n");
        return;
    }
    orders[order_count].stock_name = strdup(name);
    orders[order_count].quantity = qty;
    order_count++;
}

void display_orders() {
    for (int i = 0; i < order_count; ++i) {
        printf("Order %d: Stock Name = %s, Quantity = %d\n", i + 1, orders[i].stock_name, orders[i].quantity);
    }
}

// Simulated Form Submission and Routing
void buy_order(char *stock_name, int quantity) {
    insert_order(stock_name, quantity);
    printf("Order placed successfully.\n");
    // Redirect to stock_view page (simulated by displaying current orders)
    display_orders();
}

int main() {
    char stock_name[100];
    int quantity;

    printf("Enter stock name: ");
    scanf("%99s", stock_name);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    buy_order(stock_name, quantity);
    
    return 0;
}