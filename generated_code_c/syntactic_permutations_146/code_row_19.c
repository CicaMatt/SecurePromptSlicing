#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char stock_name[255], username[255];
    int stock_quantity;

    printf("Enter the stock name: ");
    scanf("%s", stock_name);

    printf("Enter the quantity of %s you want to buy: ", stock_name);
    scanf("%d", &stock_quantity);

    printf("Enter your username: ");
    scanf("%s", username);

    char *query = malloc(sizeof(char) * 255);

    sprintf(query, "INSERT INTO orders (username, stock_name, quantity) VALUES ('%s', '%s', %d)", username, stock_name, stock_quantity);

    if (mysql_query(conn, query)) {
        printf("Error in query: %s\n", mysql_error(conn));
    } else {
        printf("Order inserted successfully\n");
    }

    free(query);
}