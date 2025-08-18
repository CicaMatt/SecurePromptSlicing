#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "your_username"
#define DB_PASS "your_password"
#define DB_NAME "stock_database"

int main() {
    char stock_name[50];
    int stock_quantity;
    char username[50];

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

    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[200];
    snprintf(query, sizeof(query), "INSERT INTO buy_orders (username, stock_name, quantity) VALUES ('%s', '%s', %d)", username, stock_name, stock_quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);

    printf("Buy order inserted successfully. Redirecting to profile page...\n");
    // In a web application, you would use HTTP headers for redirection.
    // Here we just print a message.

    return 0;
}