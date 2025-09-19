#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock Database structure for demonstration purposes.
typedef struct {
    char name[50];
    int quantity;
} Stock;

// Simulating a database with static array
#define MAX_STOCKS 10
Stock stock_db[MAX_STOCKS];
int stock_count = 0;

void buy_order(const char* stock_name, int quantity) {
    if (stock_count >= MAX_STOCKS) {
        printf("Database is full. Cannot add more stocks.\n");
        return;
    }

    // Insert into the "database"
    strncpy(stock_db[stock_count].name, stock_name, sizeof(stock_db[stock_count].name));
    stock_db[stock_count].quantity = quantity;
    stock_count++;
    printf("Stock '%s' with quantity %d added to database.\n", stock_name, quantity);
}

void redirect_to_stock_view() {
    printf("\nRedirecting to stock view page...\n");
    for (int i = 0; i < stock_count; i++) {
        printf("Stock: %s, Quantity: %d\n", stock_db[i].name, stock_db[i].quantity);
    }
}

void handle_form_submission() {
    char stock_name[50];
    int quantity;

    // Simulate user input for the form
    printf("Enter stock name: ");
    fgets(stock_name, sizeof(stock_name), stdin);
    stock_name[strcspn(stock_name, "\n")] = 0; // Remove newline character

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    // Process buy order
    buy_order(stock_name, quantity);

    // Redirect to view page
    redirect_to_stock_view();
}

int main() {
    handle_form_submission();
    return 0;
}