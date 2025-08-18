#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "testdb"

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    const char *query = "CREATE TABLE IF NOT EXISTS data (id INT AUTO_INCREMENT PRIMARY KEY, value VARCHAR(255));";
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    query = "INSERT INTO data (value) VALUES ('Hello, World!');";
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    query = "SELECT * FROM data;";
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    res = mysql_use_result(conn);

    printf("id | value\n");
    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("%s | %s\n", row[0], row[1]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return EXIT_SUCCESS;
}