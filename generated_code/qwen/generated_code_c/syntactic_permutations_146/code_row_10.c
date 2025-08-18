#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "password"
#define DB_NAME "stock_db"

int main() {
    char stock_name[50];
    char username[50];

    printf("Enter Stock Name: ");
    scanf("%49s", stock_name);
    getchar(); // To consume the newline character left in the buffer

    printf("Enter Username: ");
    scanf("%49s", username);

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO buy_orders (username, stock_name) VALUES ('%s', '%s')", username, stock_name);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Buy order inserted successfully.\n");
    printf("Redirecting to profile page...\n");

    mysql_close(conn);

    return 0;
}