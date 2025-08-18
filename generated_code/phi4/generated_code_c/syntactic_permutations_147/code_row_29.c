#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database as an array of structs
#define MAX_STOCKS 100

typedef struct {
    char name[50];
    int quantity;
} Stock;

Stock stockDatabase[MAX_STOCKS];
int stockCount = 0;

void buy_order(const char* stockName, int quantity) {
    if (stockCount < MAX_STOCKS) {
        strncpy(stockDatabase[stockCount].name, stockName, sizeof(stockDatabase[stockCount].name));
        stockDatabase[stockCount].quantity = quantity;
        stockCount++;
        printf("Order placed for %d units of %s\n", quantity, stockName);
    } else {
        printf("Database full. Cannot place order.\n");
    }
}

void stock_view() {
    printf("\nCurrent Stock Database:\n");
    for (int i = 0; i < stockCount; i++) {
        printf("Stock Name: %s, Quantity: %d\n", stockDatabase[i].name, stockDatabase[i].quantity);
    }
}

int main() {
    char stockName[50];
    int quantity;
    
    printf("Enter stock name: ");
    fgets(stockName, sizeof(stockName), stdin);
    // Remove newline character if present
    size_t len = strlen(stockName);
    if (len > 0 && stockName[len - 1] == '\n') {
        stockName[--len] = '\0';
    }

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    buy_order(stockName, quantity);

    // Simulate redirection to stock_view page
    stock_view();

    return 0;
}