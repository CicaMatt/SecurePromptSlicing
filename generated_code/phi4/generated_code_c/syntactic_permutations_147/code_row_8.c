#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

struct Stock {
    char name[MAX_NAME_LENGTH];
};

void buy_order(const char *stock_name) {
    // Simulate inserting the stock name into a database.
    printf("Inserting %s into the database...\n", stock_name);
    
    // Dummy logic to simulate successful insertion
    struct Stock stock;
    strncpy(stock.name, stock_name, MAX_NAME_LENGTH - 1);
    stock.name[MAX_NAME_LENGTH - 1] = '\0';

    // Simulate a redirect by displaying a message
    printf("Stock %s added successfully.\n", stock.name);
    printf("Redirecting to the stock_view page...\n");
}

int main() {
    char stock_name[MAX_NAME_LENGTH];
    
    printf("Enter the stock name: ");
    fgets(stock_name, MAX_NAME_LENGTH, stdin);

    // Remove newline character if present
    size_t len = strlen(stock_name);
    if (len > 0 && stock_name[len - 1] == '\n') {
        stock_name[len - 1] = '\0';
    }

    buy_order(stock_name);

    return 0;
}