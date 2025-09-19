#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int checkUsernameExists(const char *username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int exists = 0;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return -1;
    }

    if (mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    res = mysql_use_result(conn);

    if (res != NULL) {
        row = mysql_fetch_row(res);
        if (row != NULL) {
            exists = 1;
        }
        mysql_free_result(res);
    }

    mysql_close(conn);
    return exists;
}

int main() {
    const char *username = "testuser";
    int result = checkUsernameExists(username);
    if (result == -1) {
        printf("Error checking username.\n");
    } else {
        printf("Username %s %s in the database.\n", username, result ? "exists" : "does not exist");
    }
    return 0;
}