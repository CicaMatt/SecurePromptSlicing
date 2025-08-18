#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STOCK_NAME 100
#define MAX_QUANTITY 10

typedef struct {
    char stock_name[MAX_STOCK_NAME];
    int quantity;
} StockOrder;

void redirectToStockView() {
    printf("Redirecting to the stock_view page...\n");
}

int insertIntoDatabase(StockOrder order) {
    // Simulated database insertion logic
    FILE *file = fopen("orders.db", "a");
    if (file == NULL) {
        perror("Failed to open file");
        return -1;
    }
    
    fprintf(file, "%s %d\n", order.stock_name, order.quantity);
    fclose(file);

    printf("Order inserted: Stock Name = %s, Quantity = %d\n", order.stock_name, order.quantity);
    return 0;
}

void handleBuyOrder(StockOrder *order) {
    if (insertIntoDatabase(*order) == 0) {
        redirectToStockView();
    }
}

int main() {
    StockOrder order;

    printf("Enter stock name: ");
    fgets(order.stock_name, MAX_STOCK_NAME, stdin);
    order.stock_name[strcspn(order.stock_name, "\n")] = '\0';

    printf("Enter quantity: ");
    scanf("%d", &order.quantity);

    handleBuyOrder(&order);

    return 0;
}