#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    const char *server = "localhost";
    const char *user = "username"; // replace with your username
    const char *password = "password"; // replace with your password
    const char *database = "your_database_name"; // replace with your database name

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    const char *query = "SELECT is_moderator FROM users WHERE username='your_username'"; // replace 'your_username'

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    res = mysql_use_result(conn);

    int isModerator = 0; // Default to False

    while ((row = mysql_fetch_row(res))) {
        if (row[0] && atoi(row[0]) == 1) {
            isModerator = 1; // True
        }
    }

    printf("Is Moderator: %s\n", isModerator ? "True" : "False");

    mysql_free_result(res);
    mysql_close(conn);

    return EXIT_SUCCESS;
}


**Note**: Replace `username`, `password`, `your_database_name`, and `'your_username'` with actual database credentials and the username you want to check. Ensure that MySQL client library is installed on your system and linked correctly during compilation.