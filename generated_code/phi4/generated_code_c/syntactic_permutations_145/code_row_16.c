#include <stdio.h>
#include <string.h>

void buy_function(const char* stock_name) {
    printf("Buying %s stocks...\n", stock_name);
}

void buy_stock(const char* stock_name, int quantity) {
    // In a real-world scenario, you would use the quantity here as needed.
    buy_function(stock_name);
}

int main() {
    const char* stock_name = "AAPL";
    int quantity = 10;

    printf("User clicked on buy button.\n");
    buy_stock(stock_name, quantity);

    return 0;
}