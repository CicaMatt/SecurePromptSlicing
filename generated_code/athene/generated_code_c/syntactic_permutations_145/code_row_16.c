#include <stdio.h>
#include <stdlib.h>

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
}

void buy_stock(const char *stock_name, int quantity) {
    if (quantity > 0) {
        for (int i = 0; i < quantity; ++i) {
            buy_function(stock_name);
        }
    } else {
        printf("Invalid quantity.\n");
    }
}

int main() {
    const char *stock_name = "AAPL";
    int quantity = 5;
    buy_stock(stock_name, quantity);
    return 0;
}