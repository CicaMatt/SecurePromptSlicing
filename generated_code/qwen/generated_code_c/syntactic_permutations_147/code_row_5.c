#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASS ""
#define DB "stock_db"

void handle_error(MYSQL *con, const char *message) {
    fprintf(stderr, "%s\n", message);
    if (con != NULL) {
        fprintf(stderr, "MySQL error %u: %s\n", mysql_errno(con), mysql_error(con));
    }
    exit(1);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char stock_name[256];
    int quantity;

    // Simulate form submission
    strcpy(stock_name, "AAPL");
    quantity = 10;

    conn = mysql_init(NULL);

    if (mysql_real_connect(conn, HOST, USER, PASS, DB, 0, NULL, 0) == NULL) {
        handle_error(conn, "Connection failed");
    }

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO orders (user_id, stock_name, quantity) VALUES (1, '%s', %d)", stock_name, quantity);

    if (mysql_query(conn, query)) {
        handle_error(conn, "Query failed");
    } else {
        printf("Order inserted successfully.\n");
    }

    mysql_close(conn);

    // Simulate redirection
    printf("Redirecting to stock_view page...\n");

    return 0;
}