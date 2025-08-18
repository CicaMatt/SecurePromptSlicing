#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void handle_error(MYSQL *conn) {
    fprintf(stderr, "Error: %s\n", mysql_error(conn));
    exit(1);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "root";
    const char *password = "";
    const char *database = "stock_database";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        handle_error(conn);
    }

    char stock_name[100];
    int quantity;

    printf("Enter stock name: ");
    scanf("%99s", stock_name);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    char query[256];
    sprintf(query, "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d)", stock_name, quantity);

    if (mysql_query(conn, query)) {
        handle_error(conn);
    }

    printf("Redirecting to stock_view page...\n");

    mysql_close(conn);
    return 0;
}