#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int check_username_exists(const char *username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "your_username";
    const char *password = "your_password"; /* set me first */
    const char *database = "your_database";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    res = mysql_use_result(conn);

    row = mysql_fetch_row(res);
    int exists = atoi(row[0]);

    mysql_free_result(res);
    mysql_close(conn);

    return (exists > 0) ? 1 : 0;
}

int main() {
    const char *username_to_check = "example_user";
    if (check_username_exists(username_to_check)) {
        printf("Username exists.\n");
    } else {
        printf("Username does not exist.\n");
    }
    return 0;
}
 

Make sure to replace `your_username`, `your_password`, and `your_database` with your actual MySQL credentials and database name. Ensure the MySQL C API is properly installed and linked when compiling this program. You can compile it using a command like:


gcc -o check_username check_username.c $(mysql_config --cflags --libs)


And run the executable with:


./check_username