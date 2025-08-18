#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assuming a simple in-memory representation of a database
typedef struct {
    char *stock_name;
    int quantity;
} Stock;

Stock inventory[100];
int stock_count = 0;

void buy_stock(const char *stock_name, int quantity) {
    // Call the buy_function with the stock name
    buy_function(stock_name);

    // Insert into the "database"
    for (int i = 0; i < stock_count; ++i) {
        if (strcmp(inventory[i].stock_name, stock_name) == 0) {
            inventory[i].quantity += quantity;
            return;
        }
    }

    Stock new_stock;
    new_stock.stock_name = strdup(stock_name);
    new_stock.quantity = quantity;

    inventory[stock_count++] = new_stock;
}

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
    // Additional buying logic can be implemented here
}

int main() {
    const char *name1 = "AAPL";
    int qty1 = 10;

    buy_stock(name1, qty1);

    for (int i = 0; i < stock_count; ++i) {
        printf("Stock: %s, Quantity: %d\n", inventory[i].stock_name, inventory[i].quantity);
    }

    // Free allocated memory
    for (int i = 0; i < stock_count; ++i) {
        free(inventory[i].stock_name);
    }

    return 0;
}