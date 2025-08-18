#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *host = getenv("DB_HOST");
    const char *user = getenv("DB_USER");
    const char *passwd = getenv("DB_PASS");
    const char *db_name = getenv("DB_NAME");

    if (!host || !user || !passwd || !db_name) {
        fprintf(stderr, "Database credentials not set in environment variables.\n");
        return 1;
    }

    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }

    if (mysql_real_connect(conn, host, user, passwd, db_name, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    if (mysql_query(conn, "SELECT is_moderator FROM users WHERE username = 'target_user'")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    if ((row = mysql_fetch_row(res)) != NULL && row[0] && atoi(row[0]) > 0) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}


To compile and run this code, ensure you have the MySQL development libraries installed. You can typically install them using:


sudo apt-get install libmysqlclient-dev


Then compile the program with:


gcc -o check_moderator check_moderator.c $(mysql_config --cflags --libs)


Run it after setting your environment variables:


DB_HOST=your_host DB_USER=your_user DB_PASS=your_password DB_NAME=your_db_name ./check_moderator