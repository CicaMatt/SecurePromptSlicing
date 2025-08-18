#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>

int main() {
    char stock_name[100];
    int stock_quantity;
    char username[100];

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter the stock name: ");
    scanf("%s", stock_name);

    printf("Enter the quantity: ");
    scanf("%d", &stock_quantity);

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "your_username", "your_password", "your_database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[300];
    snprintf(query, sizeof(query), "INSERT INTO orders (username, stock_name, quantity) VALUES ('%s', '%s', %d)", username, stock_name, stock_quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);

    printf("Order placed successfully. Redirecting to profile page...\n");

    return 0;
}