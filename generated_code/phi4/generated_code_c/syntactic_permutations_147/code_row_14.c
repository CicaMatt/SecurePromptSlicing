#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 100

typedef struct {
    char stock_name[MAX_NAME_LEN];
    int quantity;
} Order;

void buy_order(Order *order) {
    // Simulated database insertion
    printf("Inserting into database...\n");
    printf("Stock Name: %s\n", order->stock_name);
    printf("Quantity: %d\n", order->quantity);

    // Redirect to stock_view page
    stock_view(order);
}

void stock_view(Order *order) {
    printf("\n--- Stock View ---\n");
    printf("Stock Name: %s\n", order->stock_name);
    printf("Quantity: %d\n", order->quantity);
}

int main() {
    Order order;
    
    printf("Enter the stock name: ");
    scanf("%99s", order.stock_name);

    printf("Enter the quantity: ");
    scanf("%d", &order.quantity);

    buy_order(&order);

    return 0;
}