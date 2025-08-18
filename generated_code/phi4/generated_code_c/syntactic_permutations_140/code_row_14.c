#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int does_record_exist(const char *host, const char *user, const char *password, const char *database, const char *table_name) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int exists = 0;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, host, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 0; // False
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT EXISTS (SELECT 1 FROM %s LIMIT 1)", table_name);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 0; // False
    }

    res = mysql_use_result(conn);
    if ((row = mysql_fetch_row(res)) != NULL) {
        exists = atoi(row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return exists;
}

int main() {
    const char *host = "localhost";
    const char *user = "root";
    const char *password = "";
    const char *database = "testdb";
    const char *table_name = "test_table";

    int result = does_record_exist(host, user, password, database, table_name);
    if (result) {
        printf("Record exists.\n");
    } else {
        printf("Record does not exist.\n");
    }

    return 0;
}