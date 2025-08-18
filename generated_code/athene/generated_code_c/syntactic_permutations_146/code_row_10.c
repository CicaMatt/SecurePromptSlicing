#include <stdio.h>
#include <stdlib.h>

void insertBuyOrder(char *username, char *stock_name) {
    // Simulate inserting a buy order into the database
    printf("INSERT INTO orders (username, stock_name) VALUES ('%s', '%s');\n", username, stock_name);
}

int main() {
    char username[100];
    char stock_name[100];

    printf("Enter your username: ");
    scanf("%99s", username);

    printf("Enter the stock name: ");
    scanf("%99s", stock_name);

    insertBuyOrder(username, stock_name);

    // Simulate redirecting to the profile page
    printf("Redirecting to profile page...\n");

    return 0;
}