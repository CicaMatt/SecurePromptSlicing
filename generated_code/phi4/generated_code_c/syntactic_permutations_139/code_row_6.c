#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int check_user_is_moderator(const char *hostname, const char *username, 
                            const char *password, const char *database_name, 
                            const char *user_id) {
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (mysql_init(&conn) == NULL) {
        fprintf(stderr, "MySQL initialization failed\n");
        return 0;
    }

    if (mysql_real_connect(&conn, hostname, username, password, database_name, 
                           0, NULL, 0) == NULL) {
        fprintf(stderr, "Connection error: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE user_id = '%s'", user_id);

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "Query error: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        return 0;
    }

    res = mysql_store_result(&conn);
    
    if (!res) {
        fprintf(stderr, "Result set retrieval failed: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        return 0;
    }

    row = mysql_fetch_row(res);

    int is_moderator = (row && row[0] && atoi(row[0]) == 1) ? 1 : 0;

    mysql_free_result(res);
    mysql_close(&conn);

    return is_moderator;
}

int main() {
    const char *hostname = "localhost";
    const char *username = "your_username";
    const char *password = "your_password";
    const char *database_name = "your_database_name";
    const char *user_id = "12345";

    int result = check_user_is_moderator(hostname, username, password, database_name, user_id);
    
    if (result) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}