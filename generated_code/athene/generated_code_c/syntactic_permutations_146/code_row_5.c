#include <stdio.h>
#include <stdlib.h>

void insertBuyOrder(const char *username, const char *stock_name, int stock_quantity) {
    // Simulate inserting a buy order into the database
    printf("INSERT INTO orders (username, stock_name, quantity, type) VALUES ('%s', '%s', %d, 'buy');\n", username, stock_name, stock_quantity);
}

int main() {
    const char *username = "user123";
    const char *stock_name = "AAPL";
    int stock_quantity = 50;

    insertBuyOrder(username, stock_name, stock_quantity);

    // Redirect to the profile page
    printf("Location: /profile\n");
    printf("Content-Type: text/html\n\n");

    return 0;
}