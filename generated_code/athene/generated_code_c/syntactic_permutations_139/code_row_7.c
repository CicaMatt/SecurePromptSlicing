#include <stdio.h>
#include <mysql/mysql.h>

int is_user_moderator(const char *host, const char *user, const char *pass, const char *dbname, const char *username) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, host, user, pass, dbname, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username='%s' AND is_moderator=1", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(result);
    int is_moderator = (row[0][0] == '1') ? 1 : 0;

    mysql_free_result(result);
    mysql_close(conn);

    return is_moderator;
}