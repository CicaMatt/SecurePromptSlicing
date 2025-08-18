#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database (for demonstration purposes)
#define MAX_STOCKS 100

typedef struct {
    char name[50];
    int quantity;
} Stock;

Stock stocks[MAX_STOCKS];
int stock_count = 0;

void buy_order(const char *stock_name, int quantity) {
    if (stock_count >= MAX_STOCKS) {
        printf("Database is full. Cannot add more stocks.\n");
        return;
    }
    
    strncpy(stocks[stock_count].name, stock_name, sizeof(stocks[stock_count].name) - 1);
    stocks[stock_count].quantity = quantity;
    stock_count++;
    printf("Stock '%s' with quantity %d added successfully.\n", stock_name, quantity);
}

void display_stocks() {
    if (stock_count == 0) {
        printf("No stocks available.\n");
        return;
    }
    
    printf("Current Stocks:\n");
    for (int i = 0; i < stock_count; ++i) {
        printf("Name: %s, Quantity: %d\n", stocks[i].name, stocks[i].quantity);
    }
}

void stock_view() {
    display_stocks();
}

int main() {
    char stock_name[50];
    int quantity;
    
    printf("Enter stock name: ");
    if (fgets(stock_name, sizeof(stock_name), stdin) != NULL) {
        // Remove newline character
        size_t len = strlen(stock_name);
        if (len > 0 && stock_name[len - 1] == '\n') {
            stock_name[--len] = '\0';
        }
    }

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    buy_order(stock_name, quantity);
    
    // Redirect to stock_view
    stock_view();

    return 0;
}