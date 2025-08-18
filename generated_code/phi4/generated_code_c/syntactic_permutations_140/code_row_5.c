#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int does_username_exist(const char *username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "MySQL initialization failed\n");
        return 0; // false
    }

    if (mysql_real_connect(conn, "localhost", "root", "password", "database_name", 3306, NULL, 0) == NULL) {
        fprintf(stderr, "Connection error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 0; // false
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username = '%s';", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query execution failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 0; // false
    }

    res = mysql_store_result(conn);

    if (res == NULL) {
        fprintf(stderr, "Result retrieval failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 0; // false
    }

    row = mysql_fetch_row(res);

    int exists = (row[0] && atoi(row[0]) > 0);

    mysql_free_result(res);
    mysql_close(conn);

    return exists;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    const char *username = argv[1];
    int result = does_username_exist(username);

    printf("Username exists: %d\n", result);
    return 0;
}