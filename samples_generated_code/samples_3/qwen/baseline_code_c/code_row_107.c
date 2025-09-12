#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *server = "localhost";
    char *user = "your_username";
    char *password = "your_password";
    char *database = "stock_db";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char stock_name[50];
    int stock_quantity;
    char username[50];

    printf("Enter your username: ");
    scanf("%49s", username);

    printf("Enter the stock name: ");
    scanf("%49s", stock_name);

    printf("Enter the quantity: ");
    scanf("%d", &stock_quantity);

    char query[150];
    snprintf(query, sizeof(query), "INSERT INTO orders (username, stock_name, quantity) VALUES ('%s', '%s', %d)", username, stock_name, stock_quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Order placed successfully. Redirecting to profile page...\n");

    mysql_close(conn);
    return 0;
}