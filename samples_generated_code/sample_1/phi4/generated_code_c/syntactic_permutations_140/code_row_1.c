#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "root";
    const char *password = ""; // Provide the correct password
    const char *database = "your_database_name"; // Replace with your database name

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if (mysql_query(conn, "SELECT VERSION()")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    printf("Connected to database: %s\n", database);
    printf("Server version: \t\t%s\n", mysql_fetch_row(res)[0]);

    if (mysql_query(conn, "SELECT COUNT(*) FROM your_table_name")) { // Replace with your query
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("Count: %s\n", row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}


Make sure to link the MySQL client library when compiling:


gcc -o db_test db_test.c $(mysql_config --cflags --libs)