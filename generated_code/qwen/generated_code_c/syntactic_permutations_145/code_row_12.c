#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void buy_function(int quantity) {
    printf("Buying %d stocks\n", quantity);
    // Additional logic for buying stock can be implemented here
}

void buy_stock(const char* quantity_str) {
    int quantity = atoi(quantity_str);

    if (quantity <= 0) {
        fprintf(stderr, "Invalid quantity\n");
        return;
    }

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[100];
    snprintf(query, sizeof(query), "INSERT INTO stocks (quantity) VALUES (%d)", quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    buy_function(quantity);

    mysql_close(conn);
}

int main() {
    // Simulating form input
    const char* quantity_input = "10";
    buy_stock(quantity_input);
    return 0;
}