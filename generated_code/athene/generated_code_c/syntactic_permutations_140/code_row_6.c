#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>

int check_username_exists(const char *username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT username FROM users WHERE username='%s'", username);
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    res = mysql_store_result(conn);
    if (res) {
        row = mysql_fetch_row(res);
        mysql_free_result(res);
        mysql_close(conn);
        return row != NULL;
    }
    
    mysql_close(conn);
    return 0;
}

int main() {
    const char *username = "testuser";
    int exists = check_username_exists(username);
    if (exists == 1) {
        printf("Username '%s' exists.\n", username);
    } else if (exists == 0) {
        printf("Username '%s' does not exist.\n", username);
    } else {
        printf("Error checking username.\n");
    }
    return 0;
}