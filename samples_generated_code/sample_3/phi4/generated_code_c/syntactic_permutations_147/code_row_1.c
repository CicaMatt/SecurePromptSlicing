#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STOCK_NAME 100

typedef struct {
    char name[MAX_STOCK_NAME];
    int quantity;
} Stock;

void buy_order(Stock stock) {
    // Simulate inserting data into a database
    printf("Inserting stock: %s, Quantity: %d\n", stock.name, stock.quantity);

    // Redirect to the stock_view page (simulated)
    stock_view(stock);
}

void stock_view(Stock stock) {
    printf("\n--- Stock View Page ---\n");
    printf("Stock Name: %s\n", stock.name);
    printf("Quantity: %d\n", stock.quantity);
    printf("-----------------------\n");
}

int main() {
    Stock stock;
    
    // Simulate user entering data
    printf("Enter stock name: ");
    fgets(stock.name, MAX_STOCK_NAME, stdin);
    stock.name[strcspn(stock.name, "\n")] = '\0';  // Remove newline character

    printf("Enter quantity: ");
    scanf("%d", &stock.quantity);

    // Clear input buffer after reading integer
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}

    buy_order(stock);
    
    return 0;
}