#include <stdio.h>
#include <string.h>

#define MAX_STOCK_NAME_LENGTH 100

typedef struct {
    char stock_name[MAX_STOCK_NAME_LENGTH];
    int quantity;
} StockOrder;

void insert_order_into_database(StockOrder order) {
    printf("Inserting into database...\n");
    printf("Stock Name: %s\n", order.stock_name);
    printf("Quantity: %d\n", order.quantity);
    // Simulating insertion into a database
}

void redirect_to_stock_view() {
    printf("Redirecting to stock view page...\n");
}

int main() {
    StockOrder order;
    
    printf("Enter stock name: ");
    scanf("%99s", order.stock_name);

    printf("Enter quantity: ");
    scanf("%d", &order.quantity);
    
    insert_order_into_database(order);
    redirect_to_stock_view();

    return 0;
}