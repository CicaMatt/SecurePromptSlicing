#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "username"; // replace with actual username
    const char *password = "password"; // replace with actual password
    const char *database = "your_database_name"; // replace with actual database name

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    const char *query = "SELECT is_moderator FROM users WHERE username='your_username'"; // replace 'your_username' with actual username

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    int isModerator = 0;
    while ((row = mysql_fetch_row(res))) {
        if (row[0] && strcmp(row[0], "true") == 0) { // Assuming 'is_moderator' is stored as a string 'true' or 'false'
            isModerator = 1;
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    printf("%s\n", isModerator ? "True" : "False");

    return 0;
}