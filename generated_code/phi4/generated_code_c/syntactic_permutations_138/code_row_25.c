#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void handle_request(MYSQL *conn, const char *username) {
    char query[256];
    sprintf(query, "SELECT role FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    int num_rows = mysql_num_rows(result);
    if (num_rows == 0) {
        printf("User not found.\n");
    } else {
        MYSQL_ROW row = mysql_fetch_row(result);
        if (strcmp(row[0], "moderator") == 0) {
            printf("User is a moderator.\n");
        } else {
            printf("User is not a moderator.\n");
        }
    }

    mysql_free_result(result);
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    // Simulate a web request with username
    const char *username = "test_user";
    handle_request(conn, username);

    mysql_close(conn);
    return 0;
}


**Note:** This code assumes that you have a MySQL database running locally with a table named `users` and a column named `role`. You need to replace `"localhost"`, `"user"`, `"password"`, and `"database_name"` with your actual database credentials. Also, ensure that the MySQL client library is installed and properly linked during compilation.