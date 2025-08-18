#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int checkUsernameExists(MYSQL *conn, const char *username) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    int exists = 0;

    char query[256];
    snprintf(query, sizeof(query), "SELECT username FROM users WHERE username='%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res))) {
        exists = 1;
    }

    mysql_free_result(res);
    return exists;
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;

    const char *server = "localhost";
    const char *user = "your_username";
    const char *password = "your_password";
    const char *database = "your_database";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    const char *username_to_check = "testuser";
    int exists = checkUsernameExists(conn, username_to_check);

    if (exists == -1) {
        printf("Error checking for username.\n");
    } else {
        printf("Username %s %s in the database.\n", username_to_check, exists ? "exists" : "does not exist");
    }

    mysql_close(conn);
    return 0;
}