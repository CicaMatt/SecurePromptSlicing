#include <stdio.h>
#include <string.h>

typedef struct {
    char stock_name[50];
    int quantity;
} Stock;

void buy_function(const char *stock_name) {
    // Simulate buying process, e.g., printing to console
    printf("Buying stock: %s\n", stock_name);
}

int insert_stock(Stock *stock_array, int current_size, const char *stock_name, int quantity) {
    if (current_size >= 100) { // Assume a max size for simplicity
        return -1;
    }
    
    strcpy(stock_array[current_size].stock_name, stock_name);
    stock_array[current_size].quantity = quantity;
    return current_size + 1; // Return new array size
}

void buy_stock(const char *stock_name, int quantity) {
    static Stock stock_array[100];
    static int current_size = 0;

    current_size = insert_stock(stock_array, current_size, stock_name, quantity);
    
    if (current_size == -1) {
        printf("Error: Cannot add more stocks.\n");
        return;
    }

    buy_function(stock_name);
}

int main() {
    char stock_name[50];
    int quantity;

    // Simulate user input
    strcpy(stock_name, "AAPL");
    quantity = 10;

    buy_stock(stock_name, quantity);

    return 0;
}