#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 100

typedef struct {
    char name[MAX_NAME_LEN];
    int quantity;
} StockOrder;

void buy_order(StockOrder *order) {
    // Simulate inserting into a database (e.g., printing to console for demonstration)
    printf("Inserting order into database:\n");
    printf("Stock Name: %s\n", order->name);
    printf("Quantity: %d\n", order->quantity);
}

void stock_view() {
    printf("Redirected to Stock View Page.\n");
}

int main() {
    char name[MAX_NAME_LEN];
    int quantity;

    // Simulate user input
    printf("Enter stock name: ");
    fgets(name, MAX_NAME_LEN, stdin);
    name[strcspn(name, "\n")] = '\0';  // Remove newline character

    printf("Enter quantity: ");
    scanf("%d", &quantity);
    getchar();  // Consume the newline character left by scanf

    StockOrder order;
    strcpy(order.name, name);
    order.quantity = quantity;

    buy_order(&order);

    stock_view();

    return 0;
}