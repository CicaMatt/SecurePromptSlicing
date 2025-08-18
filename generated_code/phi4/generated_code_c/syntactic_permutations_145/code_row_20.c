#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
}

void insert_into_database(MYSQL *conn, const char *stock_name, int quantity) {
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2];
    my_ulonglong affected_rows;

    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        return;
    }

    const char *query = "INSERT INTO stocks (name, quantity) VALUES (?, ?)";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare() failed: %s\n", mysql_stmt_error(stmt));
        return;
    }

    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)stock_name;

    bind[1].buffer_type = MYSQL_TYPE_LONG;
    bind[1].buffer = (char *)&quantity;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed: %s\n", mysql_stmt_error(stmt));
        return;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute() failed: %s\n", mysql_stmt_error(stmt));
        return;
    }

    affected_rows = mysql_stmt_affected_rows(stmt);
    printf("Inserted %llu rows.\n", affected_rows);

    mysql_stmt_close(stmt);
}

void on_buy_button_click(MYSQL *conn) {
    char stock_name[256];
    int quantity;

    printf("Enter stock name: ");
    scanf("%255s", stock_name);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    insert_into_database(conn, stock_name, quantity);
    buy_function(stock_name);
}

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    on_buy_button_click(conn);

    mysql_close(conn);
    return EXIT_SUCCESS;
}