#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STOCK_NAME_LENGTH 50

typedef struct {
    char name[MAX_STOCK_NAME_LENGTH];
    int quantity;
} Stock;

void buy_order(Stock *stock) {
    // This function simulates inserting stock into a database
    printf("Inserting into database: Stock Name = %s, Quantity = %d\n", stock->name, stock->quantity);
}

int main() {
    Stock new_stock;
    
    printf("Enter the stock name: ");
    scanf("%49s", new_stock.name); // Limit input to avoid buffer overflow
    
    printf("Enter the quantity: ");
    scanf("%d", &new_stock.quantity);
    
    buy_order(&new_stock);
    
    printf("Redirecting to stock_view page...\n");
    
    return 0;
}