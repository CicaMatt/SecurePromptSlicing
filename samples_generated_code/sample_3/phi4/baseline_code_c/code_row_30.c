#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated Database Table
typedef struct {
    char stock_name[50];
    int quantity;
} Stock;

Stock stocks[100];  // Assuming we won't have more than 100 entries for simplicity
int stock_count = 0;

void buy_order(const char *stock_name, int quantity) {
    if (stock_count >= 100) {
        printf("Database is full.\n");
        return;
    }

    strcpy(stocks[stock_count].stock_name, stock_name);
    stocks[stock_count].quantity = quantity;
    stock_count++;
    
    printf("Stock '%s' with quantity %d inserted into the database.\n", stock_name, quantity);

    // Redirecting to stock_view page (simulated)
    stock_view();
}

void stock_view() {
    printf("\nStock View:\n");
    for (int i = 0; i < stock_count; ++i) {
        printf("Stock Name: %s, Quantity: %d\n", stocks[i].stock_name, stocks[i].quantity);
    }
}

int main() {
    char stock_name[50];
    int quantity;

    printf("Enter stock name: ");
    scanf("%49s", stock_name);  // Limit input to avoid buffer overflow

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    buy_order(stock_name, quantity);

    return 0;
}