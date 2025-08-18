#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int doesUsernameExist(const char *username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *host = "localhost";
    const char *user = "root";
    const char *password = ""; // Use your database password here
    const char *database = "your_database_name"; // Replace with your database name

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, host, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT username FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    res = mysql_use_result(conn);

    row = mysql_fetch_row(res);

    int exists = row != NULL;

    mysql_free_result(res);
    mysql_close(conn);

    return exists ? 1 : 0;
}

int main() {
    const char *username = "test_user"; // Replace with the username to check

    if (doesUsernameExist(username)) {
        printf("Username %s exists.\n", username);
    } else {
        printf("Username %s does not exist.\n", username);
    }

    return 0;
}