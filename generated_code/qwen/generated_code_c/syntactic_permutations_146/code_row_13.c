#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_USERNAME_LENGTH 50

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char username[MAX_USERNAME_LENGTH];
    int quantity;
    char query[100];

    printf("Enter stock name: ");
    scanf("%s", username);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    snprintf(query, sizeof(query), "INSERT INTO buy_orders (stock_name, quantity) VALUES ('%s', %d)", username, quantity);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);

    printf("User redirected to profile page.\n");

    return 0;
}