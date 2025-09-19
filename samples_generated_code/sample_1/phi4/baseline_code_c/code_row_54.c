#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int check_username_exists(const char *host, const char *user, const char *password, const char *database, const char *username) {
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (mysql_init(&conn) == NULL) {
        fprintf(stderr, "MySQL initialization failed\n");
        return 0;
    }

    if (!mysql_real_connect(&conn, host, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "Connection to MySQL server failed: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username = '%s'", mysql_real_escape_string(&conn, (char *)username));

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "Failed to execute query: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        return 0;
    }

    res = mysql_store_result(&conn);

    if (!res) {
        fprintf(stderr, "Failed to retrieve query results: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        return 0;
    }

    row = mysql_fetch_row(res);
    int count = atoi(row[0]);

    mysql_free_result(res);
    mysql_close(&conn);

    return count > 0;
}

int main() {
    const char *host = "localhost";
    const char *user = "root";
    const char *password = "your_password";
    const char *database = "your_database";
    const char *username_to_check = "test_user";

    int exists = check_username_exists(host, user, password, database, username_to_check);
    
    if (exists) {
        printf("Username exists.\n");
    } else {
        printf("Username does not exist.\n");
    }

    return 0;
}