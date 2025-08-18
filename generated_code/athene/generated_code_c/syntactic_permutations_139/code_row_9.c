#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int is_moderator(const char *username, const char *host, const char *user, const char *password, const char *dbname) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, host, user, password, dbname, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username = '%s'", username);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    res = mysql_store_result(conn);
    if (res && (row = mysql_fetch_row(res))) {
        int is_moderator = atoi(row[0]);
        mysql_free_result(res);
        mysql_close(conn);
        return is_moderator;
    } else {
        mysql_free_result(res);
        mysql_close(conn);
        return 0;
    }
}

int main() {
    const char *host = "localhost";
    const char *user = "your_user";
    const char *password = "your_password";
    const char *dbname = "your_dbname";
    const char *username = "test_user";

    int result = is_moderator(username, host, user, password, dbname);
    if (result == 1) {
        printf("User is a moderator.\n");
    } else if (result == 0) {
        printf("User is not a moderator.\n");
    } else {
        fprintf(stderr, "Error checking user moderation status.\n");
    }

    return 0;
}