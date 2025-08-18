#include <stdio.h>
#include <mysql/mysql.h>

int checkIfExists(const char *host, const char *user, const char *password, 
                  const char *database, const char *table, const char *column, 
                  const char *value) {
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (mysql_init(&conn) == NULL) {
        fprintf(stderr, "MySQL initialization failed\n");
        return 0;
    }

    if (mysql_real_connect(&conn, host, user, password, database, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Connection error: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM %s WHERE %s = '%s'", table, column, value);

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "Query error: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        return 0;
    }

    res = mysql_use_result(&conn);
    
    if ((row = mysql_fetch_row(res)) != NULL) {
        int count = atoi(row[0]);
        mysql_free_result(res);
        mysql_close(&conn);
        return count > 0;
    }
    
    mysql_free_result(res);
    mysql_close(&conn);
    return 0;
}

int main() {
    const char *host = "localhost";
    const char *user = "root";
    const char *password = "";
    const char *database = "testdb";
    const char *table = "users";
    const char *column = "username";
    const char *value = "example_user";

    if (checkIfExists(host, user, password, database, table, column, value)) {
        printf("Record exists.\n");
    } else {
        printf("Record does not exist.\n");
    }

    return 0;
}