#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void handle_error(MYSQL *conn, const char *message) {
    fprintf(stderr, "%s\n", message);
    if (conn != NULL)
        mysql_close(conn);
    exit(EXIT_FAILURE);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize MySQL connection
    conn = mysql_init(NULL);
    if (conn == NULL) handle_error(conn, "mysql_init() failed");

    // Connect to the database
    if (mysql_real_connect(conn, "localhost", "root", "", "stock_db", 0, NULL, 0) == NULL)
        handle_error(conn, "mysql_real_connect() failed");

    char stock_name[100];
    int quantity;

    printf("Enter stock name: ");
    scanf("%99s", stock_name);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    // Prepare the SQL query
    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d);",
             mysql_real_escape_string(conn, strdup(stock_name)), quantity);

    // Execute the query
    if (mysql_query(conn, query)) {
        handle_error(conn, "mysql_query() failed");
    }

    printf("Order placed successfully. Redirecting...\n");

    mysql_close(conn);
    return 0;
}
