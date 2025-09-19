#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *user = getenv("DB_USER");
    const char *password = getenv("DB_PASSWORD");
    const char *database = "your_database_name";  // Replace with your database name
    const char *host = "localhost";
    
    if (!user || !password) {
        fprintf(stderr, "Database credentials not found in environment variables.\n");
        return EXIT_FAILURE;
    }

    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "MySQL initialization failed\n");
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, host, user, password, database, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    const char *query = "SELECT is_moderator FROM users WHERE username = 'your_username';"; // Replace 'your_username' with the actual username
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    res = mysql_use_result(conn);

    row = mysql_fetch_row(res);
    if (row && row[0] && strcmp(row[0], "1") == 0) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    mysql_free_result(res);
    mysql_close(conn);
    
    return EXIT_SUCCESS;
}


Make sure to replace `your_database_name` and `'your_username'` with the actual database name and username, respectively. This code assumes you have a table called `users` with at least two columns: `username` and `is_moderator`, where `is_moderator` is stored as '1' for moderators and '0' otherwise. Also, ensure that your MySQL development library is installed on your system to compile this program using a command like:


gcc -o check_moderator check_moderator.c $(mysql_config --cflags --libs)


And set the environment variables `DB_USER` and `DB_PASSWORD` before running the compiled executable.