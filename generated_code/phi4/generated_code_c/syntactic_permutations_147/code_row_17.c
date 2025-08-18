#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 100

struct Order {
    char stock_name[MAX_NAME_LEN];
    int quantity;
};

// Simulated database as an array of orders
#define DATABASE_SIZE 10
int db_index = 0;
struct Order order_database[DATABASE_SIZE];

void buy_order(char *stock_name, int quantity) {
    if (db_index < DATABASE_SIZE) {
        strcpy(order_database[db_index].stock_name, stock_name);
        order_database[db_index].quantity = quantity;
        db_index++;
        printf("Order for %d units of %s has been placed.\n", quantity, stock_name);
        printf("Redirecting to stock_view page...\n");
    } else {
        printf("Database is full. Cannot place more orders.\n");
    }
}

void stock_view() {
    printf("\nStock View:\n");
    for (int i = 0; i < db_index; i++) {
        printf("Stock: %s, Quantity: %d\n", order_database[i].stock_name, order_database[i].quantity);
    }
}

int main() {
    char stock_name[MAX_NAME_LEN];
    int quantity;

    printf("Enter stock name: ");
    fgets(stock_name, MAX_NAME_LEN, stdin);
    stock_name[strcspn(stock_name, "\n")] = '\0';  // Remove newline character

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    buy_order(stock_name, quantity);
    stock_view();

    return 0;
}