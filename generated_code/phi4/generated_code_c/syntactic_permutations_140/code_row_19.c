#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int check_username_exists(const char *username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    // Connect to the database
    if (!mysql_real_connect(conn, "localhost", "root", "password", "database_name", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 0;
    }

    // Prepare query
    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username = '%s'", username);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res))) {
        int count = atoi(row[0]);
        free(result);
        mysql_free_result(res);
        mysql_close(conn);
        return count > 0 ? 1 : 0;
    }

    // Clean up
    free(result);
    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}

int main() {
    const char *username = "testuser";
    int exists = check_username_exists(username);
    
    if (exists) {
        printf("Username %s exists.\n", username);
    } else {
        printf("Username %s does not exist.\n", username);
    }

    return 0;
}
