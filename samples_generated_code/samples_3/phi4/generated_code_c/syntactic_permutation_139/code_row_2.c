#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "username"; // Replace with actual username
    const char *password = "password"; // Replace with actual password
    const char *database = "database_name"; // Replace with actual database name

    conn = mysql_init(NULL);
    
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    const char *query = "SELECT is_moderator FROM users WHERE username='example_user'"; // Replace 'example_user' with actual user
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    int isModerator = 0;
    while ((row = mysql_fetch_row(res))) {
        if (row[0] && atoi(row[0]) == 1) {
            isModerator = 1;
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    printf("%d\n", isModerator); // Output 1 for True, 0 for False

    return 0;
}
