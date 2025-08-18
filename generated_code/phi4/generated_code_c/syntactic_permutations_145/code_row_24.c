#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void buy_function(const char *stock_name) {
    printf("Buying %d shares of %s\n", quantity, stock_name);
}

int connect_to_database(MYSQL **conn) {
    *conn = mysql_init(NULL);
    if (*conn == NULL) {
        fprintf(stderr, "MySQL initialization failed.\n");
        return 1;
    }

    if (mysql_real_connect(*conn, "localhost", "user", "password", "database", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(*conn));
        mysql_close(*conn);
        *conn = NULL;
        return 1;
    }
    return 0;
}

void disconnect_from_database(MYSQL *conn) {
    if (conn != NULL) {
        mysql_close(conn);
    }
}

int insert_into_database(MYSQL *conn, const char *stock_name, int quantity) {
    char query[256];
    sprintf(query, "INSERT INTO stocks (name, quantity) VALUES ('%s', %d);", stock_name, quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    printf("Inserted %d shares of %s into the database.\n", quantity, stock_name);
    return 0;
}

void buy_stock(const char *stock_name, int quantity) {
    MYSQL *conn;
    
    if (connect_to_database(&conn)) {
        fprintf(stderr, "Failed to connect to the database.\n");
        exit(1);
    }

    if (insert_into_database(conn, stock_name, quantity)) {
        fprintf(stderr, "Failed to insert data into the database.\n");
        disconnect_from_database(conn);
        exit(1);
    }

    buy_function(stock_name);

    disconnect_from_database(conn);
}

int main() {
    const char *stock_name = "AAPL";
    int quantity = 10;

    buy_stock(stock_name, quantity);

    return 0;
}