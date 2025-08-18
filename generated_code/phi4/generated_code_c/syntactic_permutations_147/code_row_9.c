#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 100

typedef struct {
    char name[MAX_NAME_LEN];
    int quantity;
} StockOrder;

void buy_order(StockOrder order) {
    // Simulated database insertion
    printf("Inserting into database: %s, Quantity: %d\n", order.name, order.quantity);
    
    // Redirect to stock_view (simulated)
    stock_view(order.name);
}

void stock_view(const char* stock_name) {
    // Simulate viewing the stock in a web page
    printf("Viewing stock: %s\n", stock_name);
}

int main() {
    StockOrder order;
    
    printf("Enter stock name: ");
    fgets(order.name, MAX_NAME_LEN, stdin);
    order.name[strcspn(order.name, "\n")] = '\0'; // Remove newline character
    
    printf("Enter quantity: ");
    scanf("%d", &order.quantity);
    getchar(); // Consume the remaining newline

    buy_order(order);

    return 0;
}