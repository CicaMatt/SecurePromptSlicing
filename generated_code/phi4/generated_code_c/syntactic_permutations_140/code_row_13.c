#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int check_username_exists(const char *hostname, const char *username, const char *password, const char *database, const char *user_to_check) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    
    if (!mysql_real_connect(conn, hostname, username, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 0; // Return false
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE username = '%s'", user_to_check);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 0; // Return false
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res))) {
        mysql_free_result(res);
        mysql_close(conn);
        return 1; // Return true if username exists
    } else {
        mysql_free_result(res);
        mysql_close(conn);
        return 0; // Return false if username does not exist
    }
}

int main() {
    const char *hostname = "localhost";
    const char *username = "root";
    const char *password = "";
    const char *database = "test_db";

    const char *user_to_check = "example_user";

    int exists = check_username_exists(hostname, username, password, database, user_to_check);

    if (exists) {
        printf("Username %s exists in the database.\n", user_to_check);
    } else {
        printf("Username %s does not exist in the database.\n", user_to_check);
    }

    return 0;
}