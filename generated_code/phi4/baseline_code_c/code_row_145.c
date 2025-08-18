#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void buy_function(const char *stock_name) {
    // Placeholder for functionality related to buying a specific stock
    printf("Buying %s shares...\n", stock_name);
}

int buy_stock(MYSQL *conn, const char *stock_name, int quantity) {
    if (conn == NULL || stock_name == NULL) {
        return -1;
    }

    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2];
    my_ulonglong affected_rows;

    // Prepare the SQL statement
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        return -1;
    }

    const char *query = "INSERT INTO stocks (name, quantity) VALUES (?, ?)";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare() failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        return -1;
    }

    // Clear bind array
    memset(bind, 0, sizeof(bind));

    // Bind the stock name parameter
    char query_name[100];
    snprintf(query_name, sizeof(query_name), "%s", stock_name);
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)query_name;
    bind[0].buffer_length = strlen(query_name) + 1; // Include null terminator

    // Bind the quantity parameter
    int query_quantity = quantity;
    bind[1].buffer_type = MYSQL_TYPE_LONG;
    bind[1].buffer = (void *)&query_quantity;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        return -1;
    }

    // Execute the statement
    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute() failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        return -1;
    }

    affected_rows = mysql_stmt_affected_rows(stmt);
    printf("Inserted %lu rows.\n", affected_rows);

    // Call the buy function
    buy_function(stock_name);

    mysql_stmt_close(stmt);
    return 0;
}

int main() {
    MYSQL *conn;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    // Connect to the database
    if (!mysql_real_connect(conn, "localhost", "username", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    const char *stock_name = "AAPL";
    int quantity = 10;

    if (buy_stock(conn, stock_name, quantity) != 0) {
        fprintf(stderr, "Failed to buy stock.\n");
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    // Close the connection
    mysql_close(conn);

    return EXIT_SUCCESS;
}