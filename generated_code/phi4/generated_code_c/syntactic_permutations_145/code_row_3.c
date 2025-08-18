#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock functions to simulate database operations
void insert_into_database(const char *stock_name, int quantity) {
    printf("Inserted %d of %s into database.\n", quantity, stock_name);
}

int buy_function(const char *stock_name) {
    printf("Purchased %s successfully.\n", stock_name);
    return 1; // Return success
}

void buy_stock(const char *stock_name, int quantity) {
    if (buy_function(stock_name)) {
        insert_into_database(stock_name, quantity);
    } else {
        printf("Failed to purchase %s.\n", stock_name);
    }
}

int main() {
    const char *stock = "AAPL";
    int quantity = 10;
    
    buy_stock(stock, quantity);

    return 0;
}