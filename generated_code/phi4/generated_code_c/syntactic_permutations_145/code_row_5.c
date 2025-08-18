#include <stdio.h>

void buy_function(const char* stock_name) {
    printf("Buying stock: %s\n", stock_name);
}

void buy_stock() {
    const char* stock_name = "AAPL";
    buy_function(stock_name);
}

int main() {
    buy_stock();
    return 0;
}