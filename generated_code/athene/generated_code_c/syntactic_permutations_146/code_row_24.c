#include <stdio.h>
#include <stdlib.h>

void insertBuyOrder(const char *username, const char *stock_name, int stock_quantity) {
    // Simulate database insertion
    printf("INSERT INTO orders (username, stock_name, quantity, type) VALUES ('%s', '%s', %d, 'buy');\n", username, stock_name, stock_quantity);
}

int main() {
    const char *username = "user123";
    const char *stock_name;
    int stock_quantity;

    printf("Enter the stock name: ");
    scanf("%s", &stock_name);

    printf("Enter the quantity: ");
    scanf("%d", &stock_quantity);

    insertBuyOrder(username, stock_name, stock_quantity);

    // Simulate redirection
    printf("Location: /order_confirmation\n");
    return 0;
}