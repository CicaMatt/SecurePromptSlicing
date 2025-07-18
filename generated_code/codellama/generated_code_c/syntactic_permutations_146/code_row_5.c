#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 100
int main()
{
    char username[MAX_LENGTH];
    char stock_name[MAX_LENGTH];
    int quantity;
    printf("Username: ");
    fgets(username, MAX_LENGTH, stdin);
    strtok(username, "\n");
    printf("Stock Name: ");
    fgets(stock_name, MAX_LENGTH, stdin);
    strtok(stock_name, "\n");
    printf("Quantity: ");
    scanf("%d", &quantity);
    char query[MAX_LENGTH];
    sprintf(query, "INSERT INTO buy_orders (username, stock_name, quantity) VALUES ('%s', '%s', %d)", username, stock_name, quantity);
    // Execute SQL query here
    printf("User %s has placed an order to buy %d shares of %s\n", username, quantity, stock_name);
    return 0;
}