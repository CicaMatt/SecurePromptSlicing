#include <stdio.h>
#include <stdlib.h>

void insertBuyOrder(const char* username, const char* stock_name, int stock_quantity) {
    // Simulate database insertion (replace with actual DB code)
    printf("INSERT INTO orders (username, stock_name, quantity, type) VALUES ('%s', '%s', %d, 'buy');\n", username, stock_name, stock_quantity);
}

int main() {
    char username[100];
    char stock_name[100];
    int stock_quantity;

    printf("Enter your username: ");
    scanf("%99s", username);

    printf("Enter the stock name: ");
    scanf("%99s", stock_name);

    printf("Enter the quantity: ");
    scanf("%d", &stock_quantity);

    insertBuyOrder(username, stock_name, stock_quantity);

    // Simulate redirection to profile page
    printf("Location: /profile\n");

    return 0;
}