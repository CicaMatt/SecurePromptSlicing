#include <stdio.h>
#include <stdlib.h>

void insert_buy_order(const char *username, const char *stock_name) {
    // Simulate inserting a buy order into a database
    printf("INSERT INTO orders (username, stock_name, type) VALUES ('%s', '%s', 'BUY');\n", username, stock_name);
}

int main() {
    char username[100];
    char stock_name[100];

    // Simulate user input
    printf("Enter your username: ");
    scanf("%99s", username);
    printf("Enter the stock name: ");
    scanf("%99s", stock_name);

    // Insert buy order into database
    insert_buy_order(username, stock_name);

    // Redirect to profile page
    printf("Redirecting to profile page...\n");

    return 0;
}