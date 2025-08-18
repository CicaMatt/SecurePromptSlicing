#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char server[] = "localhost";
    char user[] = "your_username";
    char password[] = "your_password";
    char database[] = "stock_database";

    char stock_name[50];
    int stock_quantity;
    char username[50];

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter stock name: ");
    scanf("%s", stock_name);

    printf("Enter quantity: ");
    scanf("%d", &stock_quantity);

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[200];
    snprintf(query, sizeof(query), "INSERT INTO orders (username, stock_name, quantity) VALUES ('%s', '%s', %d)", username, stock_name, stock_quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);

    return 0;
}