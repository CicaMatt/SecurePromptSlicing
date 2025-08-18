#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int is_moderator(const char* username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int result = 0;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, 
                             getenv("DB_HOST"), 
                             getenv("DB_USER"), 
                             getenv("DB_PASS"), 
                             getenv("DB_NAME"), 
                             0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res))) {
        result = atoi(row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return result;
}

int main() {
    const char* username = "example_user";
    int moderator = is_moderator(username);
    printf("Is %s a moderator? %s\n", username, moderator ? "True" : "False");
    return 0;
}