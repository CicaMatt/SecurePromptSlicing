#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "stock_db"

void handle_error(MYSQL *conn, const char *msg) {
    fprintf(stderr, "%s\n", msg);
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
}

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (conn == NULL) {
        handle_error(conn, "mysql_init() failed");
    }

    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        handle_error(conn, "mysql_real_connect() failed");
    }

    char stock_name[100];
    int quantity;

    printf("Enter stock name: ");
    scanf("%99s", stock_name);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO buy_orders (stock_name, quantity) VALUES ('%s', %d)", stock_name, quantity);

    if (mysql_query(conn, query)) {
        handle_error(conn, "mysql_query() failed");
    }

    printf("Data inserted successfully. Redirecting to stock_view page...\n");

    mysql_close(conn);
    return 0;
}


**Note**: You need a MySQL server running with a database named `stock_db` and a table `buy_orders` having columns `stock_name` (VARCHAR) and `quantity` (INT). Also, ensure that the MySQL C client library is installed on your system.