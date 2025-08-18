#include <stdio.h>
#include <string.h>

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
}

void buy_stock(const char *stock_name) {
    buy_function(stock_name);
}

int main() {
    const char *stock = "AAPL";
    buy_stock(stock);
    return 0;
}