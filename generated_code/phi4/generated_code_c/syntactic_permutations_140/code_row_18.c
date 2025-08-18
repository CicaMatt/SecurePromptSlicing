#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int doesUsernameExist(const char *host, const char *user, const char *password, const char *database, const char *username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init() failed\n");
        return 0;
    }
    
    if (mysql_real_connect(conn, host, user, password, database, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Failed to connect to MySQL: Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Failed to execute query: Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);

    int exists = atoi(row[0]) > 0;

    mysql_free_result(res);
    mysql_close(conn);

    return exists;
}

int main() {
    const char *host = "localhost";
    const char *user = "your_username";
    const char *password = "your_password";
    const char *database = "your_database";

    const char *username = "test_user";

    if (doesUsernameExist(host, user, password, database, username)) {
        printf("Username exists.\n");
    } else {
        printf("Username does not exist.\n");
    }

    return 0;
}