#include <mysql/mysql.h>

bool is_moderator(const char *username, const char *password) {
    MYSQL mysql;
    mysql_init(&mysql);

    if (!mysql_real_connect(&mysql,
                            "localhost",
                            username,
                            password,
                            "mydb",
                            0,
                            NULL,
                            0)) {
        return false;
    }

    char query[256];
    sprintf(query, "SELECT is_moderator FROM users WHERE username = '%s'", username);
    MYSQL_RES *res = mysql_query(&mysql, query);

    if (!res) {
        return false;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    if (row == NULL) {
        return false;
    }

    bool is_moderator = strcmp(row[0], "1") == 0;

    mysql_free_result(res);
    mysql_close(&mysql);

    return is_moderator;
}