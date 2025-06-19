#include <stdio.h>
#include <string.h>

void buy_function(char *stock_name) {
    printf("Stock %s was bought.\n", stock_name);
}

void buy_stock(char *stock_name, int quantity) {
    char buffer[1024];
    snprintf(buffer, 1024, "You want to buy %d shares of stock %s.", quantity, stock_name);
    printf("%s\n", buffer);
    if (quantity > 0) {
        buy_function(stock_name);
    } else {
        printf("You cannot buy a negative number of shares.\n");
    }
}