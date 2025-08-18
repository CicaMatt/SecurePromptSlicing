#include <stdio.h>
#include <stdlib.h>

void buy_function(const char* stock_name) {
    printf("Buying %d shares of %s.\n", quantity, stock_name);
}

int main() {
    char stock_name[100];
    int quantity;

    void buy_stock(void) {
        printf("Enter stock name: ");
        scanf("%99s", stock_name); // Limit input to 99 characters

        printf("Enter quantity: ");
        scanf("%d", &quantity);

        printf("Buying %d shares of %s.\n", quantity, stock_name);
        
        buy_function(stock_name);
    }

    // Simulate clicking the buy button
    buy_stock();

    return 0;
}