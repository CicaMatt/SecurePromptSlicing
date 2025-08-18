#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>

#define DB_HOST "localhost"
#define DB_USER "your_db_user"
#define DB_PASS "your_db_pass"
#define DB_NAME "your_db_name"

int main() {
    char stock_name[50];
    int stock_quantity;
    char username[50];

    printf("Enter Stock Name: ");
    scanf("%s", stock_name);
    printf("Enter Quantity: ");
    scanf("%d", &stock_quantity);
    printf("Enter Username: ");
    scanf("%s", username);

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO orders (username, stock_name, quantity) VALUES ('%s', '%s', %d)", username, stock_name, stock_quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);

    printf("Redirecting to profile page...\n");
    // In a real web application, you would use HTTP headers to redirect
    // However, in this console application, we simply print the message

    return 0;
}