#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int ret = 0;

    char *server = "localhost";
    char *user = "root";
    char *password = "password"; 
    char *database = "your_database_name";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    const char *username_to_check = "testuser";
    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username='%s'", username_to_check);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    if (res == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    while ((row = mysql_fetch_row(res)) != NULL) {
        ret = atoi(row[0]) > 0;
    }

    mysql_free_result(res);
    mysql_close(conn);

    printf("%s\n", ret ? "true" : "false");

    return 0;
}