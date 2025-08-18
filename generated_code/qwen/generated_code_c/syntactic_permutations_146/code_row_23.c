#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main() {
    char stock_name[100];
    int stock_quantity;
    char username[50];

    printf("Enter Stock Name: ");
    scanf("%99s", stock_name);

    printf("Enter Quantity: ");
    scanf("%d", &stock_quantity);

    printf("Enter Username: ");
    scanf("%49s", username);

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "your_username", "your_password", "your_database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO orders (username, stock_name, quantity) VALUES ('%s', '%s', %d)", username, stock_name, stock_quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Buy order inserted successfully.\n");

    mysql_close(conn);

    // Redirect logic can be implemented based on the environment.
    // For example, in a web application, you might use HTTP headers to redirect.
    // In this console application, we simply print a message.
    printf("Redirecting...\n");

    return 0;
}